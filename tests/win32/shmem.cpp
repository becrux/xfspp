/* tests/win32/shmem.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"

#include "win32/shmem.hpp"

TEST_CASE("StartUp", "[XFS Manager]")
{
  SECTION("loading library")
  {
    REQUIRE(true);
  }
}

extern "C" int wmain(int, wchar_t **, wchar_t **)
{
  int catchArgc = 4;
  char *catchArgv[] = { "", "-s", "-d", "yes" };

  return Catch::Session().run(catchArgc,catchArgv);
}
