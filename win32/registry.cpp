/* win32/registry.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <tuple>

#include "win32/registry.hpp"

using namespace Windows::Registry;

Key::Key(const std::wstring &sPath, bool create) :
  Handle< HKEY,LSTATUS >(openKey(sPath,HKEY_CURRENT_USER,create,_disposition),RegCloseKey)
{

}

Key::Key(const std::wstring &sPath, HKEY rootKey, bool create) :
  Handle< HKEY,LSTATUS >(openKey(sPath,rootKey,create,_disposition),RegCloseKey)
{

}

HKEY Key::openKey(const std::wstring &sPath, HKEY rootKey, bool create, DWORD &dwDisposition)
{
  HKEY hKey;
  LONG err = ERROR_SUCCESS;

  if (create)
  {
    if ((err = RegCreateKeyEx(rootKey,sPath.c_str(),0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition)) != ERROR_SUCCESS)
    {
      SetLastError(static_cast< DWORD >(err));
      hKey = NULL;
    }
  }
  else
  {
    if ((err = RegOpenKeyEx(rootKey,sPath.c_str(),0,KEY_ALL_ACCESS,&hKey)) != ERROR_SUCCESS)
    {
      SetLastError(static_cast< DWORD >(err));
      hKey = NULL;
    }

    dwDisposition = REG_OPENED_EXISTING_KEY;
  }

  return hKey;
}

DWORD Key::disposition() const
{
  return _disposition;
}

void Key::remove(const std::wstring &sSubPath)
{
  LONG err;

  if ((err = RegDeleteKeyEx(handle(),sSubPath.c_str(),0,0)) != ERROR_SUCCESS)
  {
    SetLastError(static_cast< DWORD >(err));
    throw Exception();
  }
}

void Key::removeValue(const std::wstring &sValueName)
{
  LONG err;

  if ((err = RegDeleteValue(handle(), sValueName.c_str())) != ERROR_SUCCESS)
  {
    SetLastError(static_cast< DWORD >(err));
    throw Exception();
  }
}

std::set< std::wstring > Key::subKeys() const
{
  std::set< std::wstring > res;

  LONG err;

  DWORD items = 0;
  DWORD maxSubKeyLen = 0;
  if ((err = RegQueryInfoKey(handle(),NULL,NULL,NULL,&items,&maxSubKeyLen,NULL,NULL,NULL,NULL,NULL,NULL)) != ERROR_SUCCESS)
  {
    SetLastError(static_cast< DWORD >(err));
    throw Exception();
  }

  for (DWORD i = 0; i < items; ++i)
  {
    std::wstring item(maxSubKeyLen + 1,L'\0');

    DWORD bufSize = maxSubKeyLen + 1;

    if ((err = RegEnumKeyEx(handle(),i,const_cast< LPWSTR >(item.c_str()),&bufSize,NULL,NULL,NULL,NULL)) != ERROR_SUCCESS)
    {
      SetLastError(static_cast< DWORD >(err));
      throw Exception();
    }

    item.resize(bufSize);

    res.emplace(item);
  }

  return res;
}

std::map< std::wstring,std::tuple< DWORD,std::vector< BYTE > > > Key::values() const
{
  std::map< std::wstring,std::tuple< DWORD,std::vector< BYTE > > > res;

  DWORD type;
  LONG err;

  DWORD items = 0;
  DWORD maxValueNameLen = 0;
  DWORD maxValueLen = 0;
  if ((err = RegQueryInfoKey(handle(),NULL,NULL,NULL,NULL,NULL,NULL,&items,&maxValueNameLen,&maxValueLen,NULL,NULL)) != ERROR_SUCCESS)
  {
    SetLastError(static_cast< DWORD >(err));
    throw Exception();
  }

  for (DWORD i = 0; i < items; ++i)
  {
    type = 0;
    
    DWORD bufSize = maxValueNameLen + 1;
    DWORD valueBufSize = maxValueLen + 1;
   
    std::wstring vName(bufSize,L'\0');
    std::vector< BYTE > v(valueBufSize,0);

    if ((err = RegEnumValue(handle(),i,const_cast<LPWSTR>(vName.c_str()),&bufSize,NULL,&type,v.data(),&valueBufSize)) != ERROR_SUCCESS)
    {
      SetLastError(static_cast< DWORD >(err));
      throw Exception();
    }

    res.emplace(vName,std::make_tuple(type,v));
  }

  return res;
}

std::wstring Key::value(const std::wstring &sValueName) const
{
  DWORD bufSize = 0;
  LONG err;
  if ((err = RegGetValue(handle(),L"",sValueName.c_str(),RRF_RT_REG_SZ | RRF_NOEXPAND,NULL,NULL,&bufSize)) != ERROR_SUCCESS)
  {
    SetLastError(static_cast< DWORD >(err));
    throw Exception();
  }

  std::wstring res(bufSize / 2,L'\0');
  PVOID buf = const_cast< PVOID >(reinterpret_cast< const void * >(res.data()));
  if ((err = RegGetValue(handle(),L"",sValueName.c_str(),RRF_RT_REG_SZ | RRF_NOEXPAND,NULL,buf,&bufSize)) != ERROR_SUCCESS)
  {
    SetLastError(static_cast< DWORD >(err));
    throw Exception();
  }

  res.resize(res.size() - 2);

  return res;
}

std::wstring Key::value(const std::wstring &sValueName, const std::wstring &defaultValue) const
{
  try
  {
    return value(sValueName);
  }
  catch (const Exception &e)
  {
    if (e.code().value() == ERROR_FILE_NOT_FOUND)
      return defaultValue;
    else
      throw;
  }
}

void Key::setValue(const std::wstring &sValueName, const std::wstring &tValue)
{
  LONG err;

  if ((err = RegSetValueEx(handle(),sValueName.c_str(),0,REG_SZ,reinterpret_cast< const BYTE * >(tValue.c_str()),(tValue.size() + 1) * sizeof(wchar_t))) != ERROR_SUCCESS)
  {
    SetLastError(static_cast< DWORD >(err));
    throw Exception();
  }
}
