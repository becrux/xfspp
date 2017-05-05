#include <memory>

#include "gtest/gtest.h"
#include "win32/library.hpp"
#include "common/version.hpp"

#include "xfsapi.h"

static Windows::Library *lib = nullptr;

TEST(MgrLoader, LibIsLoaded)
{
  EXPECT_NE(lib,nullptr);
}

TEST(MgrLoader, BadVersionRange)
{
  XFS::VersionRange vr(XFS::Version(3,20),XFS::Version(3,0));
  WFSVERSION xfsV;

  EXPECT_EQ(
    lib->call< HRESULT >(
      "WFSStartUp",
      vr.value(),
      &xfsV),
    WFS_ERR_INTERNAL_ERROR);
}

TEST(MgrLoader, VersionTooHigh)
{
  XFS::VersionRange vr(XFS::Version(3,30),XFS::Version(3,40));
  WFSVERSION xfsV;

  EXPECT_EQ(
    lib->call< HRESULT >(
      "WFSStartUp",
      vr.value(),
      &xfsV),
    WFS_ERR_API_VER_TOO_HIGH);
}

TEST(MgrLoader, VersionTooLow)
{
  XFS::VersionRange vr(XFS::Version(3,0),XFS::Version(3,10));
  WFSVERSION xfsV;

  EXPECT_EQ(
    lib->call< HRESULT >(
      "WFSStartUp",
      vr.value(),
      &xfsV),
    WFS_ERR_API_VER_TOO_LOW);
}

TEST(MgrLoader, InvalidPointer)
{
  XFS::VersionRange vr(XFS::Version(3,20),XFS::Version(3,20));

  EXPECT_EQ(
    lib->call< HRESULT >(
      "WFSStartUp",
      vr.value(),
      NULL),
    WFS_ERR_INVALID_POINTER);
}

TEST(MgrLoader, PlainCall)
{
  XFS::VersionRange vr(XFS::Version(3,0),XFS::Version(3,20));
  WFSVERSION xfsV;

  EXPECT_EQ(
    lib->call< HRESULT >(
      "WFSStartUp",
      vr.value(),
      &xfsV),
    WFS_SUCCESS);
}

TEST(MgrLoader, AlreadyStarted)
{
  XFS::VersionRange vr(XFS::Version(3,20),XFS::Version(3,20));
  WFSVERSION xfsV;

  EXPECT_EQ(
    lib->call< HRESULT >(
      "WFSStartUp",
      vr.value(),
      &xfsV),
    WFS_ERR_ALREADY_STARTED);
}

int wmain(int argc, wchar_t **argv, wchar_t **envp)
{
  Windows::Library l{ std::wstring(argv[1]) };
  lib = &l;
  
  ::testing::InitGoogleTest(&argc,argv);

  return RUN_ALL_TESTS();
}
