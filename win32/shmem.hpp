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
  class BaseRawSharedMemory : public Handle<>
  {
    NON_COPYABLE(BaseRawSharedMemory);

    Synch::Mutex _m;
    DWORD _size;
    LPVOID _ptr;

  protected:
    explicit BaseRawSharedMemory(DWORD dwSize, const std::wstring &sName);
    ~BaseRawSharedMemory();

    void access(std::function< void(DWORD, LPVOID) > f);
  };

  class RawSharedMemory : public BaseRawSharedMemory
  {
    NON_COPYABLE(RawSharedMemory);

  public:
    explicit RawSharedMemory(DWORD dwSize, const std::wstring &sName);
    ~RawSharedMemory();

    void access(std::function< void(DWORD, LPVOID) > f);
  };

  template< typename T >
  class SharedMemory : public BaseRawSharedMemory
  {
    NON_COPYABLE(SharedMemory);

  public:
    explicit SharedMemory(const std::wstring &sName) :
      BaseRawSharedMemory(sizeof(T),sName)
    {
      ::Log::Method m(__SIGNATURE__);
    }

    ~SharedMemory()
    {
      ::Log::Method m(__SIGNATURE__);
    }

    void access(std::function< void(T *) > f)
    {
      BaseRawSharedMemory::access([f] (DWORD, LPVOID ptr)
        {
          f(reinterpret_cast< T * >(ptr));
        });
    }
  };
}

#endif
