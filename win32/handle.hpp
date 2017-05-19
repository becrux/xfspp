/* win32/handle.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __HANDLE_HPP__
#define __HANDLE_HPP__

#include <windows.h>

#include "util/constraints.hpp"
#include "win32/exception.hpp"

namespace Windows
{
  inline BOOL __stdcall nullCloseHandle(HANDLE) { return TRUE; }

  template< typename T = HANDLE, typename R = BOOL >
  class Handle
  {
    NON_COPYABLE(Handle);

    T _h;
    R ((__stdcall *_closeF))(T);

  protected:
    void setHandle(T h, R ((__stdcall *closeF))(T) = CloseHandle)
    {
      _h = h;
      _closeF = closeF;

      if ((_h == NULL) || (_h == INVALID_HANDLE_VALUE))
        throw Exception();
    }

    explicit Handle(T h, R ((__stdcall *closeF))(T) = CloseHandle)
    {
      setHandle(h,closeF);
    }

    explicit Handle() :
      _h(NULL),
      _closeF(NULL)
    {

    }

  public:
    Handle(Handle &&o) :
      _h(o._h),
      _closeF(o._closeF)
    {
      o._h = NULL;
    }

    ~Handle()
    {
      if (_h != NULL && _closeF != NULL)
      {
        _closeF(_h);
        _h = NULL;
      }
    }

    T handle() const
    {
      return _h;
    }

    Handle &operator=(Handle &&o)
    {
      _h = o._h;
      _closeF = o._closeF;
      o._h = NULL;

      return *this;
    }

    explicit operator bool() const
    {
      return (_h != NULL) && (_h != INVALID_HANDLE_VALUE);
    }
  };
}

#endif
