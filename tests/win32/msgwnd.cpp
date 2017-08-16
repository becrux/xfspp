/* tests/win32/msgwnd.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"
#include "tests/minhook.hpp"

#include "win32/msgwnd.hpp"
#include "win32/synch.hpp"

namespace
{
  int (WINAPI * PrevPostMessageW)(HWND, UINT, WPARAM, LPARAM) = nullptr;
  LONG_PTR (WINAPI * PrevSetWindowLongPtrW)(HWND, int, LONG_PTR) = nullptr;
  BOOL (WINAPI *PrevDestroyWindowPtr)(HWND) = nullptr;

  MOCK_API_FUNCTION(ATOM,0,RegisterClassEx,const WNDCLASSEX *)
  MOCK_API_FUNCTION(HWND,NULL,CreateWindowEx,DWORD,LPCTSTR,LPCTSTR,DWORD,int,int,int,int,HWND,HMENU,HINSTANCE,LPVOID)
  MOCK_API_FUNCTION(BOOL,-1,GetMessage,LPMSG,HWND,UINT,UINT)

  BOOL WINAPI MockPostMessageW(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    PrevPostMessageW(hWnd,uMsg,wParam,lParam);

    return FALSE;
  }

  LONG_PTR WINAPI MockSetWindowLongPtrW(HWND hWnd, int nIndex, LONG_PTR dwNewLong)
  {
    LONG_PTR prevValue = PrevSetWindowLongPtrW(hWnd,nIndex,dwNewLong);

    SetLastError(ERROR_ACCESS_DENIED);

    return prevValue;
  }

  BOOL WINAPI MockDestroyWindow(HWND hWnd)
  {
    PrevDestroyWindowPtr(hWnd);

    SetLastError(ERROR_ACCESS_DENIED);

    return FALSE;
  }
}

TEST_CASE("Message window", "[Win32]")
{
  SECTION("send a message")
  {
    Windows::Synch::Semaphore s(0,1);

    REQUIRE(s);

    HWND hWnd = NULL;
    bool flag = false;

    {
      Windows::MsgWnd w(
        GetModuleHandle(NULL),
        [&s, &flag] (UINT uMsg, WPARAM wP, LPARAM lP)
          {
            if ((uMsg == (WM_USER + 1)) &&
                (wP == static_cast< WPARAM >(0x01234567)) &&
                (lP == static_cast< LPARAM >(0x89ABCDEF)))
            {
              flag = true;
              s.release();
            }
          });

      w.start();
      REQUIRE((hWnd = w.handle()) != NULL);

      REQUIRE(PostMessage(
        hWnd,
        WM_USER + 1,
        static_cast< WPARAM >(0x01234567),
        static_cast< LPARAM >(0x89ABCDEF)) != 0);

      s.acquire();
      REQUIRE(flag);
    }

    REQUIRE(PostMessage(hWnd,WM_USER + 1,0,0) == 0);
  }

  SECTION("failure")
  {
    RUN_WITH_HOOK(RegisterClassEx,
      {
        Windows::MsgWnd w(GetModuleHandle(NULL),[] (UINT, WPARAM, LPARAM) { });
        w.start();

        REQUIRE_THROWS_AS(w.close(),Windows::Exception);
      });

    RUN_WITH_HOOK(CreateWindowEx,
      {
        Windows::MsgWnd w(GetModuleHandle(NULL),[] (UINT, WPARAM, LPARAM) { });
        w.start();

        REQUIRE_THROWS_AS(w.close(),Windows::Exception);
      });

    RUN_WITH_HOOK(PostMessage,
      {
        Windows::MsgWnd w(GetModuleHandle(NULL),[] (UINT, WPARAM, LPARAM) { });
        w.start();

        REQUIRE_THROWS_AS(w.close(),Windows::Exception);
      });

    RUN_WITH_NOWIDE_HOOK(DestroyWindow,
      {
        Windows::MsgWnd w(GetModuleHandle(NULL),[] (UINT, WPARAM, LPARAM) { });
        w.start();

        REQUIRE_THROWS_AS(w.close(),Windows::Exception);
      });

    RUN_WITH_HOOK(GetMessage,
      {
         Windows::MsgWnd w(GetModuleHandle(NULL),[] (UINT, WPARAM, LPARAM) { });
         w.start();

         REQUIRE_THROWS_AS(w.close(),Windows::Exception);
      });

    RUN_WITH_HOOK(SetWindowLongPtr,
      {
        Windows::MsgWnd w(GetModuleHandle(NULL),[] (UINT, WPARAM, LPARAM) { });
        w.start();
      
        REQUIRE_THROWS_AS(w.close(),Windows::Exception);
      });
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  int err;
  RUN_WITH_MINHOOK(
  {
    CREATE_HOOK(RegisterClassEx);
    CREATE_HOOK(CreateWindowEx);
    CREATE_WITH_PREV_HOOK(PostMessage,PrevPostMessage);
    CREATE_NOWIDE_WITH_PREV_HOOK(DestroyWindow,PrevDestroyWindowPtr);
    CREATE_HOOK(GetMessage);
    CREATE_WITH_PREV_HOOK(SetWindowLongPtr,PrevSetWindowLongPtr);

    err = run(argc,argv);
  });

  return err;
}
