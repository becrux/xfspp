/* win32/thread.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include <functional>

#include "win32/handle.hpp"
#include "util/constraints.hpp"

namespace Windows
{
  class Thread : public Handle<>
  {
    bool _joined;
    std::function< void () > _f;

    static DWORD WINAPI threadProc(LPVOID lpParameter);

    NON_COPYABLE(Thread);

  public:
    explicit Thread(std::function< void () > f);
    ~Thread();

    void join();
  };
}

#endif
