/* tests/win32/string.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"
#include "tests/minhook.hpp"

#include <shlwapi.h>

#include "util/string.hpp"
#include "win32/exception.hpp"

namespace
{
  int (WINAPI * PrevWideCharToMultiByte)(UINT, DWORD, LPCWSTR, int, LPSTR, int, LPCSTR, LPBOOL) = nullptr;

  int WINAPI MockWideCharToMultiByte(UINT codePage, DWORD dwFlags, LPCWSTR lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCSTR lpDefaultChar, LPBOOL lpUsedDefaultChar)
  {
    if (!StrCmpIW(lpWideCharStr,L"BadSize"))
    {
      SetLastError(ERROR_INVALID_PARAMETER);
      return 0;
    }
    else if (!StrCmpIW(lpWideCharStr,L"BadText"))
    {
      if (lpMultiByteStr == NULL)
        return 10;
      else
      {
        SetLastError(ERROR_NO_UNICODE_TRANSLATION);
        return 0;
      }
    }
    else
      return PrevWideCharToMultiByte(codePage,dwFlags,lpWideCharStr,cchWideChar,lpMultiByteStr,cbMultiByte,lpDefaultChar,lpUsedDefaultChar);
  }

  int WINAPI MockMultiByteToWideChar(UINT, DWORD, LPCSTR lpMultiByteStr, int, LPWSTR lpWideCharStr, int)
  {
    if (!StrCmpIA(lpMultiByteStr,"BadSize"))
    {
      SetLastError(ERROR_INVALID_PARAMETER);
      return 0;
    }
    else
    {
      if (lpWideCharStr == NULL)
        return 10;
      else
      {
        SetLastError(ERROR_NO_UNICODE_TRANSLATION);
        return 0;
      }
    }
  }
}

TEST_CASE("String", "[Win32]")
{
  SECTION("success")
  {
    REQUIRE(convertTo("Test Message") == L"Test Message");
    REQUIRE(convertTo(L"Test Message") == "Test Message");
  }

  SECTION("failure")
  {
    RUN_WITH_NOWIDE_HOOK(MultiByteToWideChar,
      {
        REQUIRE_THROWS_AS(convertTo("BadSize"),Windows::Exception);
        REQUIRE_THROWS_AS(convertTo("BadText"),Windows::Exception);
      });

    RUN_WITH_NOWIDE_HOOK(WideCharToMultiByte,
      {
        REQUIRE_THROWS_AS(convertTo(L"BadSize"),Windows::Exception);
        REQUIRE_THROWS_AS(convertTo(L"BadText"),Windows::Exception);
      });
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  int err;

  RUN_WITH_MINHOOK(
    {
      CREATE_NOWIDE_WITH_PREV_HOOK(WideCharToMultiByte,PrevWideCharToMultiByte);
      CREATE_NOWIDE_HOOK(MultiByteToWideChar);

      err = run(argc,argv);
    });

  return err;
}
