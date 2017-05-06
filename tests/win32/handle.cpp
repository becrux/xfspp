/* tests/win32/handle.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#define CATCH_CONFIG_RUNNER
#include "catch/catch.hpp"

#include "win32/handle.hpp"

TEST_CASE("StartUp", "[XFS Manager]")
{
  SECTION("loading library")
  {
    REQUIRE(true);
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **envp)
{
  int catchArgc = 4;
  char *catchArgv[] = { "", "-s", "-d", "yes" };

  return Catch::Session().run(catchArgc,catchArgv);
}
