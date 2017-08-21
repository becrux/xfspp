/* tests/win32/synch.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"
#include "tests/minhook.hpp"

#include "win32/synch.hpp"
#include "win32/thread.hpp"

using namespace Windows::Synch;

namespace
{
  MOCK_API_FUNCTION(HANDLE,NULL,CreateMutex,LPSECURITY_ATTRIBUTES,BOOL,LPCWSTR)
  MOCK_API_FUNCTION(HANDLE,NULL,CreateSemaphore,LPSECURITY_ATTRIBUTES,LONG,LONG,LPCWSTR)
  MOCK_API_FUNCTION(HANDLE,NULL,CreateEvent,LPSECURITY_ATTRIBUTES,BOOL,BOOL,LPCWSTR)

  MOCK_API_NOWIDE_FUNCTION(DWORD,WAIT_FAILED,WaitForSingleObjectEx,HANDLE,DWORD,BOOL)
  MOCK_API_NOWIDE_FUNCTION(BOOL,FALSE,ReleaseMutex,HANDLE)
  MOCK_API_NOWIDE_FUNCTION(BOOL,FALSE,ReleaseSemaphore,HANDLE,LONG,LPLONG)
  MOCK_API_NOWIDE_FUNCTION(BOOL,FALSE,SetEvent,HANDLE)
}

TEST_CASE("Synch", "[Win32]")
{
  SECTION("anonymous mutex")
  {
    Mutex m;

    REQUIRE(m);
  }

  SECTION("global mutex")
  {
    Mutex m(L"xfspp_test_global_mutex");

    REQUIRE(m);

    HANDLE h = OpenMutex(MUTEX_ALL_ACCESS,FALSE,L"Local\\xfspp_test_global_mutex");
    REQUIRE(h != NULL);

    CloseHandle(h);
  }

  SECTION("anonymous semaphore")
  {
    Semaphore s(0,1);

    REQUIRE(s);

    ULONGLONG startTick = GetTickCount64();
    Windows::Thread t([&s]()
      {
        SleepEx(2000,FALSE);

        s.release();
      });

    s.acquire();
    REQUIRE((GetTickCount64() - startTick) >= 1500);
  }

  SECTION("global semaphore")
  {
    Semaphore s(0,1,L"xfspp_test_global_semaphore");

    REQUIRE(s);

    HANDLE h = OpenSemaphore(SEMAPHORE_ALL_ACCESS,FALSE,L"Local\\xfspp_test_global_semaphore");
    REQUIRE(h != NULL);

    CloseHandle(h);
  }

  SECTION("anonymous event")
  {
    Event e;

    REQUIRE(e);

    ULONGLONG startTick = GetTickCount64();
    Windows::Thread t([&e] ()
    {
      SleepEx(2000,FALSE);

      e.set();
    });

    e.waitFor();
    REQUIRE((GetTickCount64() - startTick) >= 1500);
  }

  SECTION("global event")
  {
    Event e(L"xfspp_test_global_event");

    REQUIRE(e);

    HANDLE h = OpenEvent(EVENT_ALL_ACCESS,FALSE,L"Local\\xfspp_test_global_event");
    REQUIRE(h != NULL);

    CloseHandle(h);
  }

  SECTION("failure - mutex")
  {
    RUN_WITH_HOOK(CreateMutex,
    {
      REQUIRE_THROWS_AS(Mutex(),Windows::Exception);
    });

    RUN_WITH_NOWIDE_HOOK(WaitForSingleObjectEx,
    {
      Mutex m;
      REQUIRE_THROWS_AS(Locker< Mutex >(m),Windows::Exception);
    });

    RUN_WITH_NOWIDE_HOOK(ReleaseMutex,
    {
      Mutex m;
      REQUIRE_THROWS_AS(Locker< Mutex >(m),Windows::Exception);
    });
  }

  SECTION("failure - semaphore")
  {
    RUN_WITH_HOOK(CreateSemaphore,
    {
      REQUIRE_THROWS_AS(Semaphore(0,1),Windows::Exception);
    });

    RUN_WITH_NOWIDE_HOOK(WaitForSingleObjectEx,
    {
      Semaphore s(0,1);
      REQUIRE_THROWS_AS(s.acquire(),Windows::Exception);
    });

    RUN_WITH_NOWIDE_HOOK(ReleaseSemaphore,
    {
      Semaphore s(0,1);
      REQUIRE_THROWS_AS(s.release(),Windows::Exception);
    });
  }

  SECTION("failure - event")
  {
    RUN_WITH_HOOK(CreateEvent,
    {
      REQUIRE_THROWS_AS(Event(),Windows::Exception);
    });

    RUN_WITH_NOWIDE_HOOK(WaitForSingleObjectEx,
    {
      Event e;
      REQUIRE_THROWS_AS(e.waitFor(),Windows::Exception);
    });

    RUN_WITH_NOWIDE_HOOK(SetEvent,
    {
      Event e;
      REQUIRE_THROWS_AS(e.set(),Windows::Exception);
    });
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  int err;
  RUN_WITH_MINHOOK(
    {
      CREATE_HOOK(CreateMutex);
      CREATE_HOOK(CreateSemaphore);
      CREATE_HOOK(CreateEvent);
      CREATE_NOWIDE_HOOK(WaitForSingleObjectEx);
      CREATE_NOWIDE_HOOK(ReleaseMutex);
      CREATE_NOWIDE_HOOK(ReleaseSemaphore);
      CREATE_NOWIDE_HOOK(SetEvent);

      err = run(argc,argv);
    });

  return err;
}
