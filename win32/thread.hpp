/* win32/thread.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __WIN32_THREAD_HPP__
#define __WIN32_THREAD_HPP__

#include <functional>
#include <exception>

#include "win32/handle.hpp"
#include "util/constraints.hpp"

namespace Windows
{
  class Thread : public Handle<>
  {
    bool _joined;
    std::exception_ptr _eptr;
    std::function< void () > _f;

    static DWORD WINAPI threadProc(LPVOID lpParameter);

    NON_COPYABLE(Thread);
    
    void doJoin(bool rethrow);

  public:
    explicit Thread(std::function< void () > f);
    Thread(Thread &&o);
    ~Thread();

    void join();

    Thread &operator=(Thread &&o);
  };
}

#endif
