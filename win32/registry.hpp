#pragma once
#ifndef __REGISTRY_HPP__
#define __REGISTRY_HPP__

#include <string>
#include <map>
#include <vector>

#include "win32/handle.hpp"

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

    public:
      explicit Key(const std::wstring &sPath, HKEY rootKey = HKEY_CURRENT_USER);

      DWORD disposition() const;

      std::vector< std::wstring > subKeys() const;

      std::map< std::wstring,std::tuple< DWORD,std::vector< BYTE > > > values() const;

      Error remove(const std::wstring &sSubPath);
      Error removeValue(const std::wstring &sValueName);
      
      Error setValue(const std::wstring &sValueName,DWORD type, const std::vector< BYTE > &newValue);
    };    
  }
}

#endif
