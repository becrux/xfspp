/* tests/win32/msgwnd.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"

#include "win32/msgwnd.hpp"
#include "win32/synch.hpp"

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
              flag = true;
          
            s.release();
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
    
    REQUIRE(PostMessage(hWnd,WM_USER + 1,NULL,NULL) == 0);
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  return run(argc,argv);
}
