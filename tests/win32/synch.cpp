/* tests/win32/synch.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"

#include "win32/synch.hpp"
#include "win32/thread.hpp"

using namespace Windows::Synch;

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
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  return run(argc,argv);
}
