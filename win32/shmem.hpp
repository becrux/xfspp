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
#include "util/constraints.hpp"

namespace Windows
{
  class RawSharedMemory : private Uuid, public Handle<>
  {
    NON_COPYABLE(RawSharedMemory);

    Synch::Mutex _m;
    LPVOID _ptr;

  public:
    explicit RawSharedMemory(DWORD dwSize);
    ~RawSharedMemory();

    void access(std::function< void(LPVOID) > f);
  };

  template< typename T >
  class SharedMemory : private RawSharedMemory
  {
    NON_COPYABLE(SharedMemory);

  public:
    explicit SharedMemory() :
      RawSharedMemory(sizeof(T))
    {
      ::Log::Method m(__SIGNATURE__);
    }

    ~SharedMemory()
    {
      ::Log::Method m(__SIGNATURE__);
    }

    void access(std::function< void(T *) > f)
    {
      RawSharedMemory::access([f] (LPVOID ptr)
        {
          f(reinterpret_cast< T * >(ptr));
        });
    }
  };
}

#endif
