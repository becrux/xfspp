/* tests/xfs/version.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"

#include "xfs/version.hpp"

TEST_CASE("Version", "[XFS]")
{
  SECTION("plain")
  {
    REQUIRE(XFS::Version::min(3) == XFS::Version(0x0003));
    REQUIRE(XFS::Version::max(3) == XFS::Version(0x0FF03));

    XFS::Version v1(0x0B0A);
    
    REQUIRE(v1.value() == 0x0B0A);
    REQUIRE(v1.major() == 0xA);
    REQUIRE(v1.minor() == 0xB);

    REQUIRE(v1 < XFS::Version(0x000B));
    REQUIRE(v1 < XFS::Version(0x0C0A));
    REQUIRE(v1 > XFS::Version(0x0009));
    REQUIRE(v1 > XFS::Version(0x0A0A));

    REQUIRE(v1 == XFS::Version(0x0B0A));
    REQUIRE(v1 != XFS::Version(0x0A0A));

    REQUIRE(v1 == XFS::Version(0x0A,0x0B));
    
    std::ostringstream oss;
    oss << v1;
    
    REQUIRE(oss.str() == "10.11");
  }

  SECTION("range")
  {
    XFS::Version start(3,1);
    XFS::Version end(4,7);
    
    XFS::VersionRange vr(start,end);
    
    REQUIRE(vr.start() == start);
    REQUIRE(vr.end() == end);
    REQUIRE(vr.value() == 0x01030704);
    REQUIRE(!vr.contains(XFS::Version(0x2,0xD)));
    REQUIRE(vr.contains(start));
    REQUIRE(vr.contains(XFS::Version(0x3,0xD)));
    REQUIRE(vr.contains(end));
    REQUIRE(!vr.contains(XFS::Version(0x4,0x8)));
    REQUIRE(vr == XFS::VersionRange(start,end));
    REQUIRE(vr != XFS::VersionRange(XFS::Version(3,0),end));
    REQUIRE(vr != XFS::VersionRange(start,XFS::Version(4,8)));
    REQUIRE(vr != XFS::VersionRange(XFS::Version(3,0),XFS::Version(4,8)));

    std::ostringstream oss;
    oss << vr;
    
    REQUIRE(oss.str() == "[3.01 - 4.07]");
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  return run(argc,argv);
}
