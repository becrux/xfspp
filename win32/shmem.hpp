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

#include <cstdint>
#include <functional>

#include "win32/handle.hpp"
#include "win32/synch.hpp"
#include "util/memory.hpp"

namespace Windows
{
  class SharedMemory : public Handle<>
  {
    Synch::Mutex _m;
    std::uint8_t *_ptr;

  public:
    explicit SharedMemory(DWORD dwSize);
    ~SharedMemory();

    template< typename T >
    T access(DWORD dwOffset, T &oldValue, std::function< void(T &t) > f = std::function< void(T &f) >())
    {
      Synch::Locker< Synch::Mutex > lock(_m);

      T t;

      copyMem(t,_ptr + dwOffset);
      oldValue = t;

      if (f)
      {
        f(t);
        
        copyMem(_ptr + dwOffset,t);
      }

      return t;
    }

    template< typename T >
    T access(DWORD dwOffset, std::function< void(T &t) > f = std::function< void(T &f) >())
    {
      T oldValue;

      return access(dwOffset,oldValue,f);
    }

    void access(DWORD dwOffset, std::function< void(std::uint8_t *) > f);
  };
}

#endif
