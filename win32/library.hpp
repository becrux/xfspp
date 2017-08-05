/* win32/library.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __WIN32_LIBRARY_HPP__
#define __WIN32_LIBRARY_HPP__

#include <string>
#include <stdexcept>

#include "win32/handle.hpp"
#include "util/constraints.hpp"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4191)
#endif

namespace Windows
{
  class Library : public Handle< HMODULE >
  {
    NON_COPYABLE(Library);

  public:
    explicit Library(const std::wstring &sLibPath);
    ~Library();

    template< typename R, typename... Args >
    R call(LPCSTR funcName, Args... args)
    {
      auto f = reinterpret_cast< R (__stdcall *)(Args...) >(GetProcAddress(handle(),funcName));
      if (f == NULL)
        throw Exception();

      return f(args...);
    }
  };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
