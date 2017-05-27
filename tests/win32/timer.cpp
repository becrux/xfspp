/* tests/win32/timer.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"
#include "tests/minhook.hpp"

#include "win32/timer.hpp"

namespace
{
  MOCK_API_NOWIDE_FUNCTION(DWORD,WAIT_FAILED,WaitForSingleObjectEx,HANDLE,DWORD,BOOL)
}

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

  SECTION("failure")
  {
    RUN_WITH_NOWIDE_HOOK(WaitForSingleObjectEx,
    {
      bool flag = false;

      Windows::Timer t(2000,
        [&flag] ()
          {
            flag = true;
          });

      REQUIRE(t);

      SleepEx(3000,FALSE);
      REQUIRE(!flag);
    });
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  int err;
  RUN_WITH_MINHOOK(
    {
      CREATE_NOWIDE_HOOK(WaitForSingleObjectEx);
      
      err = run(argc,argv);
    });
  
  return err;
}
