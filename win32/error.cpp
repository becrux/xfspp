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
