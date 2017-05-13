/* tests/win32/registry.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"

#include "win32/registry.hpp"

using namespace Windows::Registry;

TEST_CASE("Registry", "[Win32]")
{
  SECTION("not existing - do_not_create")
  {
    Key k(L"Software\\Should_Be_An_Unknown_Key",false);

    REQUIRE(!k);
  }

  SECTION("existing - do_not_create")
  {
    Key k(L"Software\\Microsoft\\Windows\\CurrentVersion",false);

    REQUIRE(k);
    REQUIRE(k.disposition() == REG_OPENED_EXISTING_KEY);
    REQUIRE(!k.subKeys().empty());
  }

  SECTION("not existing - create")
  {
    {
      Key k(L"Software\\XFSPP_TEMP");

      REQUIRE(k);
      REQUIRE(k.disposition() == REG_CREATED_NEW_KEY);
      REQUIRE(k.subKeys().empty());
      REQUIRE(k.values().empty());

      k.setValue< DWORD >(L"ValueName",0x01234567);
      REQUIRE(k.value< DWORD >(L"ValueName",0x89ABCDEF) == 0x01234567);
      REQUIRE(k.value< DWORD >(L"ValueName2",0x89ABCDEF) == 0x89ABCDEF);
      REQUIRE(k.values().size() == 1);

      k.setValue< std::string >(L"ValueName","Hello, Registry!");
      REQUIRE((k.value< std::string >(L"ValueName","Goodbye!") == "Hello, Registry!"));

      k.setValue< std::wstring >(L"ValueName",L"Hello, Wide Registry!");
      REQUIRE((k.value< std::wstring >(L"ValueName",L"Goodbye!") == L"Hello, Wide Registry!"));

      k.removeValue(L"ValueName");
      REQUIRE(k.value< DWORD >(L"ValueName",0xDEADBEEF) == 0xDEADBEEF);
      REQUIRE(k.values().empty());
    }

    {
      Key k(L"Software\\XFSPP_TEMP");

      REQUIRE(k);
      REQUIRE(k.disposition() == REG_OPENED_EXISTING_KEY);
      REQUIRE(k.subKeys().empty());
      REQUIRE(k.values().empty());
    }

    {
      Key k(L"Software");

      REQUIRE(k);
      REQUIRE(k.disposition() == REG_OPENED_EXISTING_KEY);

      k.remove(L"XFSPP_TEMP");
    }

    {
      Key k(L"Software\\XFSPP_TEMP",false);

      REQUIRE(!k);
    }
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  RegDeleteKeyEx(HKEY_CURRENT_USER,L"Software\\XFSPP_TEMP",NULL,0);

  return run(argc,argv);
}
