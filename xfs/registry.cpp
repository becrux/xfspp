/* xfs/registry.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "xfs/registry.hpp"
#include "util/memory.hpp"
#include "cen/320/xfsspi.h"

using namespace XFS::Registry;

Key::Key(Type type, const std::string &sKeyName, const std::shared_ptr< Windows::Library > &cMgrLibrary) :
  _handle(0),
  _type(type),
  _mgrLibrary(cMgrLibrary)
{
  DWORD disp;

  HKEY hKey;

  switch (type)
  {
    case Type::Root:
      hKey = WFS_CFG_HKEY_XFS_ROOT;
      break;

    case Type::Machine:
      hKey = WFS_CFG_HKEY_MACHINE_XFS_ROOT;
      break;

    case Type::User:
      hKey = WFS_CFG_HKEY_USER_DEFAULT_XFS_ROOT;
      break;

    default:
      return;
  }

  checkAndAssert(_mgrLibrary->call< HRESULT >("WFMCreateKey",hKey,sKeyName.c_str(),&_handle,&disp));
}

Key::~Key()
{
  if (_handle)
	  _mgrLibrary->call< HRESULT >(
      "WFMCloseKey",
      _handle);
}

std::string Key::value(const std::string &sValueName) const
{
  DWORD bufSize = 0;

  checkAndAssert(_mgrLibrary->call< HRESULT >("WFMQueryValue",_handle,sValueName.c_str(),NULL,&bufSize),WFS_ERR_CFG_VALUE_TOO_LONG);
  std::string res(bufSize + 1,'\0');

  checkAndAssert(_mgrLibrary->call< HRESULT >("WFMQueryValue",_handle,sValueName.c_str(),res.c_str(),&bufSize));
  return res;
}

std::string Key::value(const std::string &sValueName, const std::string &defaultValue) const
{
  try
  {
    return value(sValueName);
  }
  catch (const XFS::Exception &e)
  {
    if (e == WFS_ERR_CFG_INVALID_NAME)
      return defaultValue;
    else
      throw;
  }
}


void Key::setValue(const std::string &sValueName, const std::string &newValue) const
{
  checkAndAssert(_mgrLibrary->call< HRESULT >(
    "WFMSetValue",
    _handle,
    sValueName.c_str(),
    newValue.c_str(),
    newValue.size() + 1
  ));
}

void Key::removeValue(const std::string &sValueName)
{
  checkAndAssert(_mgrLibrary->call< HRESULT >("WFMDeleteValue",_handle,sValueName.c_str()));
}

void Key::removeKey(const std::string &sKeyName)
{
  checkAndAssert(_mgrLibrary->call< HRESULT >("WFMDeleteKey",_handle,sKeyName.c_str()));
}
