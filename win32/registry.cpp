/* win32/registry.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <tuple>

#include "win32/registry.hpp"
#include "log/log.hpp"

using namespace Windows::Registry;

Key::Key(const std::wstring &sPath, HKEY rootKey) :
  Handle< HKEY,LSTATUS >(NULL,RegCloseKey),
  _disposition(0)
{
  HKEY hKey;
  RegCreateKeyEx(rootKey,sPath.c_str(),0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&_disposition);
  setHandle(hKey);
}

DWORD Key::disposition() const
{
  return _disposition;
}

Windows::Error Key::remove(const std::wstring &sSubPath)
{
  ::Log::Method(__SIGNATURE__,WSTRING(L"sSubPath = " << sSubPath));

  return Error(RegDeleteKeyEx(handle(),sSubPath.c_str(),0,0));
}

Windows::Error Key::removeValue(const std::wstring &sValueName)
{
  ::Log::Method(__SIGNATURE__,WSTRING(L"sValueName = " << sValueName));

  return Error(RegDeleteValue(handle(), sValueName.c_str()));
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

Windows::Error Key::setValue(const std::wstring &sValueName, DWORD type, const std::vector< BYTE > &newValue)
{
  ::Log::Method(__SIGNATURE__,WSTRING(L"sValueName = " << sValueName));

  return Error(RegSetValueEx(handle(),sValueName.c_str(),0,type,newValue.data(),newValue.size()));
}
