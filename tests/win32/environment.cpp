/* tests/win32/environment.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"
#include "tests/minhook.hpp"

#include "win32/environment.hpp"
#include "win32/exception.hpp"
#include "util/memory.hpp"

using namespace Windows::Environment;

namespace
{
  MOCK_API_FUNCTION(LPWCH,NULL,GetEnvironmentStrings,VOID)
  MOCK_API_FUNCTION(BOOL,FALSE,SetEnvironmentVariable,LPCWSTR,LPCWSTR)
}

TEST_CASE("Environment", "[Win32]")
{
  SECTION("initialize")
  {
    REQUIRE_NOTHROW(CREATE_INSTANCE(Manager));
    REQUIRE(INSTANCE(Manager).has(L"PATH"));
    REQUIRE(INSTANCE(Manager).has(L"path"));
    REQUIRE(!INSTANCE(Manager).get(L"path").empty());
    REQUIRE(INSTANCE(Manager).get(L"XFSPP_NOT_SHOULD_BE_EXISTING",L"Test") == L"Test");

    std::list< std::wstring > k = INSTANCE(Manager).keys();
    REQUIRE(
      std::find_if(
        std::begin(k),
        std::end(k),
        [] (const std::wstring &s1) { return icasecmp(s1,L"PATH") == 0; }) != std::end(k));

    REQUIRE_NOTHROW(DELETE_INSTANCE(Manager));
  }

  SECTION("modify")
  {
    REQUIRE_NOTHROW(CREATE_INSTANCE(Manager));

    std::wstring key = L"XFSPP_TEST_KEY";
    INSTANCE(Manager).set(key,L"Test");

    std::ostringstream oss;
    oss << INSTANCE(Manager);

    REQUIRE(oss.str().find("XFSPP_TEST_KEY=Test") != std::string::npos);

    REQUIRE(INSTANCE(Manager).get(key,L"Should_Not_Be_This") == L"Test");

    TCHAR buf[MAX_PATH];
    clearMem(buf);

    REQUIRE(GetEnvironmentVariable(key.c_str(),buf,MAX_PATH) != 0);
    REQUIRE(std::wstring(buf) == L"Test");

    RUN_WITH_HOOK(SetEnvironmentVariable,
      {
        REQUIRE_THROWS_AS(INSTANCE(Manager).remove(key),Windows::Exception);
      });

    REQUIRE_NOTHROW(INSTANCE(Manager).remove(key));

    clearMem(buf);

    REQUIRE(!INSTANCE(Manager).has(key));
    REQUIRE(((GetEnvironmentVariable(key.c_str(),buf,MAX_PATH) == 0) && (GetLastError() == ERROR_ENVVAR_NOT_FOUND)));

    REQUIRE_NOTHROW(DELETE_INSTANCE(Manager));
  }

  SECTION("failure - access env")
  {
    RUN_WITH_HOOK(GetEnvironmentStrings,
      {
        REQUIRE_THROWS_AS(CREATE_INSTANCE(Manager),Windows::Exception);
      });
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  int err;

  RUN_WITH_MINHOOK(
    {
      CREATE_HOOK(GetEnvironmentStrings);
      CREATE_HOOK(SetEnvironmentVariable);

      err = run(argc,argv);
    });

  return err;
}
