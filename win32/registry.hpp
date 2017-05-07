/* win32/registry.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __REGISTRY_HPP__
#define __REGISTRY_HPP__

#include <string>
#include <map>
#include <vector>
#include <sstream>

#include "win32/handle.hpp"
#include "util/memory.hpp"
#include "util/constraints.hpp"

namespace Windows
{
  namespace Registry
  {
    class Value
    {

    };

    class Key : public Handle< HKEY,LSTATUS >
    {
      DWORD _disposition;

      NON_COPYABLE(Key);

    public:
      explicit Key(const std::wstring &sPath, HKEY rootKey = HKEY_CURRENT_USER);

      DWORD disposition() const;

      std::vector< std::wstring > subKeys() const;

      std::map< std::wstring,std::tuple< DWORD,std::vector< BYTE > > > values() const;

      template< typename T >
      T value(const std::wstring &sValueName, const std::wstring &sSubKey, T &&defaultValue = T()) const
      {
        BYTE buf[1024];
        DWORD bufSize = 1024;

        clearMem(buf);
        if (RegGetValue(handle(),sSubKey.c_str(),sValueName.c_str(),RRF_RT_ANY | RRF_NOEXPAND,NULL,buf,&bufSize) != ERROR_SUCCESS)
          return defaultValue;

        T res;
        std::istringstream iss(std::string(buf,buf + bufSize));
        iss >> res;

        return res;
      }

      template< typename T >
      T value(const std::wstring &sValueName, T &&defaultValue = T()) const
      {
        return value(sValueName,std::wstring(),std::forward< T >(defaultValue));
      }

      Error< LRESULT > remove(const std::wstring &sSubPath);
      Error< LRESULT > removeValue(const std::wstring &sValueName);

      Error< LRESULT > setValue(const std::wstring &sValueName,DWORD type, const std::vector< BYTE > &newValue);
    };
  }
}

#endif
