/* win32/library.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __LIBRARY_HPP__
#define __LIBRARY_HPP__

#include <string>

#include "win32/handle.hpp"

namespace Windows
{
  class Library : public Handle< HMODULE >
  { 
  public:
    explicit Library(const std::wstring &sLibPath);
    ~Library();

    template< typename R, typename... Args >
    R call(LPCSTR funcName, Args... args)
    {
      return reinterpret_cast< R (__stdcall *)(Args...) >(GetProcAddress(handle(),funcName))(args...);
    }
  };
}

#endif
