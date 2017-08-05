/* tests/mgr/startup.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <memory>

#include "tests/catch.hpp"

#include "win32/library.hpp"
#include "xfs/version.hpp"

#include "xfsapi.h"

static Windows::Library *lib = nullptr;

TEST_CASE("StartUp", "[XFS Manager]")
{
  SECTION("loading library")
  {
    REQUIRE(lib != nullptr);
  }

  SECTION("passing bad version range")
  {
    XFS::VersionRange vr(XFS::Version(3,20),XFS::Version(3,0));
    WFSVERSION xfsV;
  
    REQUIRE(
      lib->call< HRESULT >(
        "WFSStartUp",
        vr.value(),
        &xfsV) == WFS_ERR_INTERNAL_ERROR);
  }
  
  SECTION("passing too high version range")
  {
    XFS::VersionRange vr(XFS::Version(3,30),XFS::Version(3,40));
    WFSVERSION xfsV;
  
    REQUIRE(
      lib->call< HRESULT >(
        "WFSStartUp",
        vr.value(),
        &xfsV) == WFS_ERR_API_VER_TOO_HIGH);
  }
  
  SECTION("passing too low version range")
  {
    XFS::VersionRange vr(XFS::Version(3,0),XFS::Version(3,10));
    WFSVERSION xfsV;
  
    REQUIRE(
      lib->call< HRESULT >(
        "WFSStartUp",
        vr.value(),
        &xfsV) == WFS_ERR_API_VER_TOO_LOW);
  }
  
  SECTION("passing invalid output pointer")
  {
    XFS::VersionRange vr(XFS::Version(3,20),XFS::Version(3,20));
  
    REQUIRE(
      lib->call< HRESULT >(
        "WFSStartUp",
        vr.value(),
        NULL) == WFS_ERR_INVALID_POINTER);
  }
  
  SECTION("working call")
  {
    XFS::VersionRange vr(XFS::Version(3,0),XFS::Version(3,20));
    WFSVERSION xfsV;
  
    REQUIRE(
      lib->call< HRESULT >(
        "WFSStartUp",
        vr.value(),
        &xfsV) == WFS_SUCCESS);
  }
  
  SECTION("check if it has already started")
  {
    XFS::VersionRange vr(XFS::Version(3,20),XFS::Version(3,20));
    WFSVERSION xfsV;
  
    REQUIRE(
      lib->call< HRESULT >(
        "WFSStartUp",
        vr.value(),
        &xfsV) == WFS_ERR_ALREADY_STARTED);
  }

  SECTION("cleanup")
  {
    XFS::VersionRange vr(XFS::Version(3,20),XFS::Version(3,20));

    REQUIRE(lib->call< HRESULT >("WFSCleanUp") == WFS_SUCCESS);
  }

  SECTION("cleanup when not started")
  {
    XFS::VersionRange vr(XFS::Version(3,20),XFS::Version(3,20));

    REQUIRE(lib->call< HRESULT >("WFSCleanUp") == WFS_ERR_NOT_STARTED);
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  std::shared_ptr< Windows::Library > l;

  return run(
    argc,
    argv,
    [&l] (const std::wstring &libArg)
      {
        std::wcout << "XFS Manager Library = " << libArg << std::endl;

        l = std::make_shared< Windows::Library >(std::wstring(libArg));
        lib = l.get();
      });
}
