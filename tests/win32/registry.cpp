/* tests/win32/registry.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"
#include "tests/minhook.hpp"

#include "win32/registry.hpp"

using namespace Windows::Registry;

namespace
{
  MOCK_API_FUNCTION(LSTATUS,RegCreateKeyEx,HKEY,LPCWSTR,DWORD,LPWSTR,DWORD,REGSAM,LPSECURITY_ATTRIBUTES,PHKEY,LPDWORD)
  MOCK_API_FUNCTION(LSTATUS,RegOpenKeyEx,HKEY,LPCWSTR,DWORD,REGSAM,PHKEY)
  MOCK_API_FUNCTION(LSTATUS,RegQueryInfoKey,HKEY,LPWSTR,LPDWORD,LPDWORD,LPDWORD,LPDWORD,LPDWORD,LPDWORD,LPDWORD,LPDWORD,LPDWORD,PFILETIME)
  MOCK_API_FUNCTION(LSTATUS,RegEnumKeyEx,HKEY,DWORD,LPWSTR,LPDWORD,LPDWORD,LPWSTR,LPDWORD,PFILETIME)
  MOCK_API_FUNCTION(LSTATUS,RegEnumValue,HKEY,DWORD,LPWSTR,LPDWORD,LPDWORD,LPDWORD,LPBYTE,LPDWORD)
  MOCK_API_FUNCTION(LSTATUS,RegGetValue,HKEY,LPCWSTR,LPCWSTR,DWORD,LPDWORD,PVOID,LPDWORD)
  MOCK_API_FUNCTION(LSTATUS,RegSetValueEx,HKEY,LPCWSTR,DWORD,DWORD,CONST BYTE *,DWORD)
  MOCK_API_FUNCTION(LSTATUS,RegDeleteValue,HKEY,LPCWSTR)
  MOCK_API_FUNCTION(LSTATUS,RegDeleteKeyEx,HKEY,LPCWSTR,REGSAM,DWORD)
}

TEST_CASE("Registry", "[Win32]")
{
  SECTION("not existing - do_not_create")
  {
    REQUIRE_THROWS_AS(Key(L"Software\\Should_Be_An_Unknown_Key",false),Windows::Exception);
  }

  SECTION("existing - do_not_create")
  {
    Key k(L"Software\\Microsoft\\Windows\\CurrentVersion",false);

    REQUIRE(k);
    REQUIRE(k.disposition() == REG_OPENED_EXISTING_KEY);
    REQUIRE(!k.subKeys().empty());
  }

  SECTION("existing - create failure")
  {
    RUN_WITH_HOOK(RegCreateKeyEx,
      {
        REQUIRE_THROWS_AS(Key(L"Software\\XFSPP_New_Mock_key"),Windows::Exception);
      });
  }

  SECTION("existing - open failure")
  {
    RUN_WITH_HOOK(RegOpenKeyEx,
      {
        REQUIRE_THROWS_AS(Key(L"Software\\Microsoft\\Windows\\CurrentVersion",false),Windows::Exception);
      });
  }

  SECTION("existing HKLM - do_not_create")
  {
    try
    {
      Key k(L"Software\\Microsoft\\Windows\\CurrentVersion",HKEY_LOCAL_MACHINE,false);

      CHECK(k);
      CHECK(k.disposition() == REG_OPENED_EXISTING_KEY);
      CHECK(!k.subKeys().empty());
    }
    catch (const Windows::Exception &)
    {
      return;
    }
  }

  SECTION("not existing - create and use")
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

      k.setValue(L"ValueName",std::string("Hello, Registry!"));
      REQUIRE((k.value(L"ValueName",std::string("Goodbye!")) == "Hello, Registry!"));

      k.setValue(L"ValueName",std::wstring(L"Hello, Wide Registry!"));
      REQUIRE((k.value(L"ValueName",std::wstring(L"Goodbye!")) == L"Hello, Wide Registry!"));

      k.removeValue(L"ValueName");
      REQUIRE(k.value< DWORD >(L"ValueName",0xDEADBEEF) == 0xDEADBEEF);
      REQUIRE(k.values().empty());

      REQUIRE(k.value(L"ValueName",std::string("Test String")) == "Test String");
      REQUIRE(k.value(L"ValueName",std::wstring(L"Test Wide String")) == L"Test Wide String");

      RUN_WITH_HOOK(RegSetValueEx,
        {
          REQUIRE_THROWS_AS(k.setValue(L"ValueName",std::wstring(L"Hello, Wide Registry!")),Windows::Exception);
        });

      RUN_WITH_HOOK(RegDeleteValue,
        {
          REQUIRE_THROWS_AS(k.removeValue(L"ValueName"),Windows::Exception);
        });
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

      RUN_WITH_HOOK(RegDeleteKeyEx,
        {
          REQUIRE_THROWS_AS(k.remove(L"XFSPP_TEMP"),Windows::Exception);
        });

      REQUIRE_NOTHROW(k.remove(L"XFSPP_TEMP"));
    }

    {
      REQUIRE_THROWS_AS(Key(L"Software\\XFSPP_TEMP",false),Windows::Exception);
    }
  }
  
  SECTION("failure - reading subkeys")
  {
    Key k(L"Software\\Microsoft\\Windows\\CurrentVersion",false);
    REQUIRE(k);

    RUN_WITH_HOOK(RegQueryInfoKey,
      {
        REQUIRE_THROWS_AS(k.subKeys(),Windows::Exception);
      });

    RUN_WITH_HOOK(RegEnumKeyEx,
      {
        REQUIRE_THROWS_AS(k.subKeys(),Windows::Exception);
      });
  }

  SECTION("failure - reading values")
  {
    Key k(L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer",false);
    REQUIRE(k);

    RUN_WITH_HOOK(RegQueryInfoKey,
      {
        REQUIRE_THROWS_AS(k.values(),Windows::Exception);
      });

    RUN_WITH_HOOK(RegEnumValue,
      {
        REQUIRE_THROWS_AS(k.values(),Windows::Exception);
      });
  }

  SECTION("failure - deleting values")
  {
    Key k(L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer",false);
    REQUIRE(k);

    RUN_WITH_HOOK(RegQueryInfoKey,
    {
      REQUIRE_THROWS_AS(k.values(),Windows::Exception);
    });

    RUN_WITH_HOOK(RegEnumValue,
    {
      REQUIRE_THROWS_AS(k.values(),Windows::Exception);
    });
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  RegDeleteKeyEx(HKEY_CURRENT_USER,L"Software\\XFSPP_TEMP",0,0);

  MH_Initialize();

  CREATE_HOOK(RegCreateKeyEx);
  CREATE_HOOK(RegOpenKeyEx);
  CREATE_HOOK(RegQueryInfoKey);
  CREATE_HOOK(RegEnumKeyEx);
  CREATE_HOOK(RegEnumValue);
  CREATE_HOOK(RegGetValue);
  CREATE_HOOK(RegSetValueEx);
  CREATE_HOOK(RegDeleteValue);
  CREATE_HOOK(RegDeleteKeyEx);

  int err = run(argc,argv);

  MH_Uninitialize();

  return err;
}
