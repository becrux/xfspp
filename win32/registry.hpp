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

      static HKEY openKey(const std::wstring &sPath, HKEY rootKey, bool create, DWORD &dwDisposition);

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
        DWORD bufSize = 0;

        LONG err;
        if ((err = RegGetValue(handle(),L"",sValueName.c_str(),RRF_RT_REG_SZ | RRF_NOEXPAND,NULL,NULL,&bufSize)) != ERROR_SUCCESS)
        {
          if (err == ERROR_FILE_NOT_FOUND)
            return defaultValue;
          else
          {
            SetLastError(static_cast< DWORD >(err));
            throw Exception();
          }
        }

        std::wstring buf(bufSize / 2,L'\0');
        PVOID pBuf = const_cast< PVOID >(reinterpret_cast< const void * >(buf.data()));

        if ((err = RegGetValue(handle(),L"",sValueName.c_str(),RRF_RT_REG_SZ | RRF_NOEXPAND,NULL,pBuf,&bufSize)) != ERROR_SUCCESS)
        {
          SetLastError(static_cast< DWORD >(err));
          throw Exception();
        }

        T res;
        std::wistringstream iss{ buf };
        iss >> res;

        return res;
      }

      void remove(const std::wstring &sSubPath);
      void removeValue(const std::wstring &sValueName);

      template< typename T >
      void setValue(const std::wstring &sValueName, const T &tValue)
      {
        std::wostringstream oss;

        oss << tValue;

        std::wstring vs(oss.str());

        LONG err;
        if ((err = RegSetValueEx(handle(),sValueName.c_str(),0,REG_SZ,reinterpret_cast< const BYTE * >(vs.c_str()),(vs.size() + 1) * sizeof(wchar_t))) != ERROR_SUCCESS)
        {
          SetLastError(static_cast< DWORD >(err));
          throw Exception();
        }
      }

      std::string value(const std::wstring &sValueName, const std::string &defaultValue = "") const;
      std::wstring value(const std::wstring &sValueName, const std::wstring &defaultValue = L"") const;
      void setValue(const std::wstring &sValueName, const std::string &tValue);
      void setValue(const std::wstring &sValueName, const std::wstring &tValue);
    };
  }
}

#endif
