/* xfs/registry.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __XFS_REGISTRY_HPP__
#define __XFS_REGISTRY_HPP__

#include <string>
#include <map>
#include <set>
#include <vector>
#include <memory>

#include "win32/library.hpp"
#include "util/memory.hpp"
#include "util/constraints.hpp"
#include "util/string.hpp"

#include "xfs/exception.hpp"

namespace XFS
{
  namespace Registry
  {
    enum class Type { Root, Machine, User };

    class Key
    {
      HKEY _handle;
      Type _type;
      std::shared_ptr< Windows::Library > _mgrLibrary;

    public:
      explicit Key(Type type, const std::string &sKeyName, const std::shared_ptr< Windows::Library > &cMgrLibrary);
      explicit Key(const std::string &sKeyName, const std::shared_ptr< Windows::Library > &cMgrLibrary) :
        Key(XFS::Registry::Type::User,sKeyName,cMgrLibrary) { }
      ~Key();

      std::string value(const std::string &sValueName) const;
      std::string value(const std::string &sValueName, const std::string &defaultValue) const;

      template< typename T >
      T value(const std::string &sValueName) const
      {
        T res;
        std::string s = value(sValueName);

        std::istringstream iss{ s };
        iss >> res;

        return res;
      }
	  
      template< typename T >
      T value(const std::string &sValueName, const T &defaultValue) const
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

      void setValue(const std::string &sValueName, const std::string &newValue) const;

      template< typename T >
      void setValue(const std::string &sValueName, const T &tValue)
      {
        std::wostringstream oss;

        oss << tValue;

        setValue(sValueName,oss.str());
      }
	  
      void removeValue(const std::string &sValueName);
      void removeKey(const std::string &sKeyName);
    };
  }
}

#endif
