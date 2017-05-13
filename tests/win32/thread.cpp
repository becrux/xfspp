/* tests/win32/thread.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"

#include "win32/thread.hpp"

TEST_CASE("Threads", "[Win32]")
{
  SECTION("simple thread")
  {
    ULONGLONG startTick = GetTickCount64();

    {
      Windows::Thread t([] ()
        {
          SleepEx(2000,FALSE);
        });
      
      REQUIRE(t);
    }

    REQUIRE((GetTickCount64() - startTick) >= 2000);
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  return run(argc,argv);
}
