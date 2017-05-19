/* tests/win32/environment.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"

#include "win32/environment.hpp"
#include "util/memory.hpp"

using namespace Windows::Environment;

TEST_CASE("Environment", "[Win32]")
{
  SECTION("initialize")
  {
    REQUIRE_NOTHROW(Manager::instance());
    REQUIRE(Manager::instance().has(L"PATH"));
    REQUIRE(Manager::instance().has(L"path"));
    REQUIRE(!Manager::instance().get(L"path").empty());
    REQUIRE(Manager::instance().get(L"XFSPP_NOT_SHOULD_BE_EXISTING",L"Test") == L"Test");

    std::list< std::wstring > k = Manager::instance().keys();
    REQUIRE(
      std::find_if(
        std::begin(k),
        std::end(k),
        [] (const std::wstring &s1) { return icasecmp(s1,L"PATH") == 0; }) != std::end(k));
  }

  SECTION("modify")
  {
    std::wstring key = L"XFSPP_TEST_KEY";
    Manager::instance().set(key,L"Test");

    std::ostringstream oss;
    oss << Manager::instance();

    REQUIRE(oss.str().find("XFSPP_TEST_KEY=Test") != std::string::npos);

    REQUIRE(Manager::instance().get(key,L"Should_Not_Be_This") == L"Test");

    TCHAR buf[MAX_PATH];
    clearMem(buf);

    REQUIRE(GetEnvironmentVariable(key.c_str(),buf,MAX_PATH) != 0);
    REQUIRE(std::wstring(buf) == L"Test");

    Manager::instance().remove(key);

    clearMem(buf);

    REQUIRE(!Manager::instance().has(key));
    REQUIRE(((GetEnvironmentVariable(key.c_str(),buf,MAX_PATH) == 0) && (GetLastError() == ERROR_ENVVAR_NOT_FOUND)));
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  return run(argc,argv);
}
