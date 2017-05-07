/* tests/win32/timer.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"

#include "win32/timer.hpp"

TEST_CASE("StartUp", "[XFS Manager]")
{
  SECTION("loading library")
  {
    REQUIRE(true);
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  return run(argc,argv);
}
