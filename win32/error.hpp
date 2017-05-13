/* win32/error.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#include <windows.h>

namespace Windows
{
  template< typename T = DWORD >
  class Error
  {
    T _value;
    T _successValue;

  public:
    explicit Error(T value = GetLastError(),const T &successValue = T()) :
      _value(value),
      _successValue(successValue)
    {

    }

    T value() const { return _value; }

    explicit operator bool() const { return _value == _successValue; }

    bool operator==(const T &other) const { return _value == other; }
    bool operator!=(const T &other) const { return _value != other; }
  };
}

#endif
