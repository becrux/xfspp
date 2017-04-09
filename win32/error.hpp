#pragma once
#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#include <windows.h>

namespace Windows
{
  class Error
  {
    DWORD _value;
    DWORD _successValue;
    
  public:
    explicit Error(DWORD value = GetLastError(), DWORD successValue = 0);

    DWORD value() const;
    
    operator bool() const;
  };
}

#endif
