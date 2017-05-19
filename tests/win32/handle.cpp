/* tests/win32/handle.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"

#include "win32/handle.hpp"
#include "win32/filesystem.hpp"

using namespace Windows;

namespace
{
  class File : public Handle<>
  {
    NON_COPYABLE(File);
    NON_MOVEABLE(File);

  public:
    explicit File(const std::wstring &fName, bool create = false) :
      Handle<>(
        CreateFile(
          (fName.empty())? FileSystem::Path::tempFileName().c_str() : fName.c_str(),
          GENERIC_READ | GENERIC_WRITE,
          0,
          NULL,
          (create)? CREATE_ALWAYS : OPEN_EXISTING,
          FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE,
          NULL))
    {

    }
  };
}

TEST_CASE("Handles", "[Win32]")
{
  SECTION("null handle")
  {
    REQUIRE_THROWS_AS(File(L"not_existing_file"),Windows::Exception);
  }

  SECTION("valid handle")
  {
    REQUIRE_NOTHROW(File(std::wstring(),true));
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  return run(argc,argv);
}
