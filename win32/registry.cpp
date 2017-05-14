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
  Handle< HKEY,LSTATUS,LONG >(NULL,RegCloseKey),
  _disposition(0)
{
  init(sPath,HKEY_CURRENT_USER,create);
}

Key::Key(const std::wstring &sPath, HKEY rootKey, bool create) :
  Handle< HKEY,LSTATUS,LONG >(NULL,RegCloseKey),
  _disposition(0)
{
  init(sPath,rootKey,create);
}

void Key::init(const std::wstring &sPath, HKEY rootKey, bool create)
{
  HKEY hKey;
  LONG err = ERROR_SUCCESS;

  if (create)
  {
    if ((err = RegCreateKeyEx(rootKey,sPath.c_str(),0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&_disposition)) != ERROR_SUCCESS)
      hKey = NULL;
  }
  else
  {
    if ((err = RegOpenKeyEx(rootKey,sPath.c_str(),0,KEY_ALL_ACCESS,&hKey)) != ERROR_SUCCESS)
      hKey = NULL;

    _disposition = REG_OPENED_EXISTING_KEY;
  }

  setHandle(hKey,err);
}

DWORD Key::disposition() const
{
  return _disposition;
}

Windows::Error< LRESULT > Key::remove(const std::wstring &sSubPath)
{
  return Error< LRESULT >(RegDeleteKeyEx(handle(),sSubPath.c_str(),0,0));
}

Windows::Error< LRESULT > Key::removeValue(const std::wstring &sValueName)
{
  return Error< LRESULT >(RegDeleteValue(handle(), sValueName.c_str()));
}

std::vector< std::wstring > Key::subKeys() const
{
  std::vector< std::wstring > res;

  TCHAR buf[1];

  DWORD idx = 0;
  DWORD bufSize = 0;
  while (RegEnumKeyEx(handle(),idx,buf,&bufSize,NULL,NULL,NULL,NULL) == ERROR_MORE_DATA)
  {
    std::wstring item(bufSize,L'\0');

    RegEnumKeyEx(handle(),idx++,const_cast< LPWSTR >(item.c_str()),&bufSize,NULL,NULL,NULL,NULL);

    res.emplace_back(item);
    bufSize = 0;
  }

  return res;
}

std::map< std::wstring,std::tuple< DWORD,std::vector< BYTE > > > Key::values() const
{
  std::map< std::wstring,std::tuple< DWORD,std::vector< BYTE > > > res;

  TCHAR buf[1];
  BYTE valueBuf[1];

  DWORD idx = 0;
  DWORD bufSize = 0;
  DWORD valueBufSize = 0;
  DWORD type = 0;
  while (RegEnumValue(handle(),idx,buf,&bufSize,NULL,&type,valueBuf,&valueBufSize) == ERROR_MORE_DATA)
  {
    std::wstring vName(bufSize,L'\0');
    std::vector< BYTE > v(valueBufSize,0);

    RegEnumValue(handle(),idx++,const_cast<LPWSTR>(vName.c_str()),&bufSize,NULL,&type,v.data(),&valueBufSize);

    res.emplace(vName,std::make_tuple(type,v));
    bufSize = valueBufSize = 0;
  }

  return res;
}

std::wstring Key::value(const std::wstring &sValueName, const std::wstring &defaultValue) const
{
  TCHAR buf[1024];
  DWORD bufSize = 1024 * sizeof(TCHAR);

  clearMem(buf);
  if (RegGetValue(handle(),L"",sValueName.c_str(),RRF_RT_REG_SZ | RRF_NOEXPAND,NULL,buf,&bufSize) != ERROR_SUCCESS)
    return defaultValue;

  return std::wstring(buf);
}

std::string Key::value(const std::wstring &sValueName,const std::string &defaultValue) const
{
  return convertTo(value(sValueName,convertTo(defaultValue)));
}

Windows::Error< LRESULT > Key::setValue(const std::wstring &sValueName,const std::wstring &tValue)
{
  return Error< LRESULT >(
    RegSetValueEx(handle(),sValueName.c_str(),0,REG_SZ,reinterpret_cast< const BYTE * >(tValue.c_str()),tValue.size() * sizeof(wchar_t)));
}

Windows::Error< LRESULT > Key::setValue(const std::wstring &sValueName, const std::string &tValue)
{
  return setValue(sValueName,convertTo(tValue));
}
