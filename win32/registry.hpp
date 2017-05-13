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
#include "util/string.hpp"

namespace Windows
{
  namespace Registry
  {
    class Key : public Handle< HKEY,LSTATUS >
    {
      DWORD _disposition;

      NON_COPYABLE(Key);

      void init(const std::wstring &sPath, HKEY rootKey, bool create);

      void readBuf(TCHAR *buf, DWORD &bufSize);

    public:
      explicit Key(const std::wstring &sPath, bool create = true);
      explicit Key(const std::wstring &sPath, HKEY rootKey, bool create = true);

      DWORD disposition() const;

      std::vector< std::wstring > subKeys() const;

      std::map< std::wstring,std::tuple< DWORD,std::vector< BYTE > > > values() const;

      template< typename T >
      T value(const std::wstring &sValueName, const T &defaultValue = T()) const
      {
        TCHAR buf[1024];
        DWORD bufSize = 1024 * sizeof(TCHAR);

        clearMem(buf);
        if (RegGetValue(handle(),L"",sValueName.c_str(),RRF_RT_REG_SZ | RRF_NOEXPAND,NULL,buf,&bufSize) != ERROR_SUCCESS)
          return defaultValue;

        T res;
        std::wistringstream iss{ std::wstring(buf,buf + bufSize) };
        iss >> res;

        return res;
      }

      template<>
      std::wstring value(const std::wstring &sValueName, const std::wstring &defaultValue) const
      {
        TCHAR buf[1024];
        DWORD bufSize = 1024 * sizeof(TCHAR);

        clearMem(buf);
        if (RegGetValue(handle(),L"",sValueName.c_str(),RRF_RT_REG_SZ | RRF_NOEXPAND,NULL,buf,&bufSize) != ERROR_SUCCESS)
          return defaultValue;

        return std::wstring(buf);
      }

      template<>
      std::string value< std::string >(const std::wstring &sValueName,const std::string &defaultValue) const
      {
        return convertTo(value< std::wstring >(sValueName,convertTo(defaultValue)));
      }

      Error< LRESULT > remove(const std::wstring &sSubPath);
      Error< LRESULT > removeValue(const std::wstring &sValueName);

      template< typename T >
      Error< LRESULT > setValue(const std::wstring &sValueName, const T &tValue)
      {
        std::wostringstream oss;

        oss << tValue;

        std::wstring vs(oss.str());

        return Error< LRESULT >(
          RegSetValueEx(handle(),sValueName.c_str(),0,REG_SZ,reinterpret_cast< const BYTE * >(vs.c_str()),vs.size() * sizeof(wchar_t)));
      }

      template<>
      Error< LRESULT > setValue< std::string >(const std::wstring &sValueName, const std::string &tValue)
      {
        return setValue< std::wstring >(sValueName,convertTo(tValue));
      }
    };
  }
}

#endif
