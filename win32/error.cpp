/* win32/error.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "win32/error.hpp"

using namespace Windows;

Error::Error(DWORD iValue, DWORD iSuccessValue) :
  _value(iValue),
  _successValue(iSuccessValue)
{
    
}

DWORD Error::value() const
{
  return _value;
}

Error::operator bool() const
{
  return _value == _successValue;
}
