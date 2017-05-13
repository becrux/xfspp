/* tests/win32/timer.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"

#include "win32/timer.hpp"

TEST_CASE("Timers", "[Win32]")
{
  SECTION("triggered")
  {
    bool flag = false;

    Windows::Timer t(2000,
      [&flag] ()
        {
          flag = true;
        });

    REQUIRE(t);

    SleepEx(3000,FALSE);
    REQUIRE(flag);
  }

  SECTION("cancelled")
  {
    bool flag = false;

    Windows::Timer t(2000,
      [&flag] ()
    {
      flag = true;
    });

    REQUIRE(t);

    SleepEx(500,FALSE);
    t.cancel();
    SleepEx(2000,FALSE);
    REQUIRE(!flag);
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  return run(argc,argv);
}
