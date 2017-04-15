/* win32/shmem.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __SHMEM_HPP__
#define __SHMEM_HPP__

#include <functional>

#include "win32/handle.hpp"
#include "win32/synch.hpp"
#include "win32/uuid.hpp"
#include "log/log.hpp"
#include "util/memory.hpp"

namespace Windows
{
  template< typename T >
  class SharedMemory : private Uuid, public Handle<>
  {
    Synch::Mutex _m;
    LPVOID _ptr;

  public:
    explicit SharedMemory() :
      Handle<>(CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(T),value(L"Global\\XFSPP_XFS_MANAGER_SHMEM_").c_str())),
      _m(value(L"Global\\XFSPP_XFS_MANAGER_SHMEM_MUTEX_")),
      _ptr(MapViewOfFileEx(handle(),FILE_MAP_ALL_ACCESS,0,0,0,NULL))
    {
      ::Log::Method m(__FUNCSIG__);
    }

    ~SharedMemory()
    {
      ::Log::Method m(__FUNCSIG__);

      UnmapViewOfFile(_ptr);
    }

    void access(std::function< void(T *) > f)
    {
      Synch::Locker< Synch::Mutex > lock(_m);

      f(reinterpret_cast< T * >(_ptr));
    }
  };
}

#endif
