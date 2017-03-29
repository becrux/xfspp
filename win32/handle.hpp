#pragma once
#ifndef __HANDLE_HPP__
#define __HANDLE_HPP__

#include <windows.h>

namespace Windows
{
  class Handle
  {
    Handle(const Handle &o);
    Handle &operator=(const Handle &o);

    HANDLE _h;
    int (_stdcall *_closeF)(HANDLE);

  protected:
    void setHandle(HANDLE h);

    explicit Handle(HANDLE h = NULL,
                    int (_stdcall *closeF)(HANDLE) = CloseHandle);

  public:
    Handle(Handle &&o);
    ~Handle();

    HANDLE handle() const;

    Handle &operator=(Handle &&o);
  };
}

#endif
