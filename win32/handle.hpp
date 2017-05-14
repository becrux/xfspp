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

#include "win32/error.hpp"
#include "util/constraints.hpp"

namespace Windows
{
  inline BOOL __stdcall nullCloseHandle(HANDLE) { return TRUE; }

  template< typename T = HANDLE, typename R = BOOL, typename E = DWORD >
  class Handle
  {
    NON_COPYABLE(Handle);

    T _h;
    Error< E > _lastError;
    R ((__stdcall *_closeF))(T);

    void setLastError()
    {
      _lastError = ((_h == NULL) || (_h == INVALID_HANDLE_VALUE))? Error< E >() : Error< E >(ERROR_SUCCESS);
    }

  protected:
    void setHandle(T h, E errorValue)
    {
      _h = h;
      _lastError = Error< E >(errorValue);
    }

    void setHandle(T h)
    {
      _h = h;
      setLastError();
    }

    explicit Handle(T h = NULL,
                    R ((__stdcall *closeF))(T) = CloseHandle) :
      _h(h),
      _closeF(closeF)
    {
      setLastError();
    }

  public:
    Handle(Handle &&o) :
      _h(o._h),
      _lastError(o._lastError)
    {
      _closeF = o._closeF;
      o._h = NULL;
      o._lastError = ERROR_SUCCESS;
    }

    ~Handle()
    {
      if (_h != NULL)
      {
        _closeF(_h);
        _h = NULL;
      }
    }

    T handle() const
    {
      return _h;
    }

    Error< E > lastError() const
    {
      return _lastError;
    }

    Handle &operator=(Handle &&o)
    {
      _h = o._h;
      _lastError = o._lastError;
      _closeF = o._closeF;
      o._h = NULL;
      o._lastError = ERROR_SUCCESS;

      return *this;
    }

    explicit operator bool() const
    {
      return (_h != NULL) && (_h != INVALID_HANDLE_VALUE);
    }
  };
}

#endif
