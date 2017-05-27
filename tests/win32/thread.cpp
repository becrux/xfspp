/* tests/win32/thread.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"
#include "tests/minhook.hpp"

#include "win32/thread.hpp"

namespace
{
  MOCK_API_NOWIDE_FUNCTION(DWORD,WAIT_FAILED,WaitForSingleObjectEx,HANDLE,DWORD,BOOL)
}

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

    REQUIRE((GetTickCount64() - startTick) >= 1500);
  }
  
  SECTION("failure")
  {
    Windows::Thread t([] ()
      {
        SleepEx(2000,FALSE);
      });

    RUN_WITH_NOWIDE_HOOK(WaitForSingleObjectEx,
      {
        REQUIRE_THROWS_AS(t.join(),Windows::Exception);
      });
  }

  SECTION("failure in thread")
  {
    Windows::Thread t([] ()
      {
        SleepEx(2000,FALSE);
        throw std::invalid_argument("error");
      });

    REQUIRE_THROWS_AS(t.join(),std::invalid_argument);
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
