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
#include <stdexcept>

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
      FARPROC WINAPI f = GetProcAddress(handle(),funcName);
      if (f == NULL)
        throw std::invalid_argument(std::string("cannot find ") + std::string(funcName));

      return reinterpret_cast< R (__stdcall *)(Args...) >(f)(args...);
    }
  };
}

#endif
