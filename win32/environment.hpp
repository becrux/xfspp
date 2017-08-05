/* win32/environment.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __WIN32_ENVIRONMENT_HPP__
#define __WIN32_ENVIRONMENT_HPP__

#include <list>
#include <map>
#include <iostream>
#include <string>

#include <windows.h>
#include "util/string.hpp"
#include "util/singleton.hpp"

namespace Windows
{
  namespace Environment
  {
    class Manager
    {
      struct CIWideLess
      {
        bool operator()(const std::wstring &s1,const std::wstring &s2) const
        {
          return icasecmp(s1,s2) < 0;
        }
      };

      std::map< std::wstring,std::wstring,CIWideLess > _vars;

      explicit Manager();

      friend std::ostream &operator<<(std::ostream &out, const Manager &m);

      friend class Singleton< Manager >;

    public:
      bool has(const std::wstring &key) const;

      std::wstring get(const std::wstring &key, const std::wstring &sDefault = std::wstring()) const;
      void set(const std::wstring &key, const std::wstring &value);
      void remove(const std::wstring &key);

      std::list< std::wstring > keys() const;
    };

    std::ostream &operator<<(std::ostream &out, const Manager &m);
  }
}

#endif
