/* win32/synch.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __SYNCH_HPP__
#define __SYNCH_HPP__

#include <string>

#include <windows.h>

#include "win32/handle.hpp"
#include "util/constraints.hpp"

namespace Windows
{
  namespace Synch
  {
    class Lockable : public Handle<>
    {
      NON_COPYABLE(Lockable);

    public:
      explicit Lockable(HANDLE h);

      void lock();
    };

    class Mutex : public Lockable
    {
      NON_COPYABLE(Mutex);

    public:
      explicit Mutex(const std::wstring &sName = std::wstring());

      void unlock();
    };

    class Semaphore : public Lockable
    {
      NON_COPYABLE(Semaphore);

    public:
      explicit Semaphore(LONG start, LONG max);

      void unlock();
    };

    class Event : public Handle<>
    {
      NON_COPYABLE(Event);

    public:
      explicit Event();

      void waitFor();
      void set();
    };

    template< typename T >
    class Locker
    {
      T &_ref;

      Locker(const Locker &);
      Locker &operator=(const Locker &);

    public:
      explicit Locker(T &ref) : _ref(ref) { _ref.lock(); }
      ~Locker() { _ref.unlock(); }
    };

    template<>
    class Locker< HANDLE >
    {
      HANDLE _ref;

      NON_COPYABLE(Locker);

    public:
      explicit Locker(HANDLE ref) : _ref(ref) { WaitForSingleObjectEx(_ref,INFINITE,FALSE); }
      Locker(Locker &&o) :
        _ref(o._ref)
      {
        o._ref = NULL;
      }

      ~Locker()
      {
        if (_ref != NULL)
          ReleaseMutex(_ref);
      }

      Locker &operator=(Locker &&o)
      {
        _ref = o._ref;
        o._ref = NULL;

        return *this;
      }
    };
  }
}

#endif
