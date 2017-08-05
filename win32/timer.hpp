/* win32/timer.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __WIN32_TIMER_HPP__
#define __WIN32_TIMER_HPP__

#include <functional>

#include "win32/synch.hpp"
#include "win32/thread.hpp"
#include "util/constraints.hpp"

namespace Windows
{
  class Timer : public Handle<>
  {
    std::function< void () > _f;
    Synch::Event _cancelEvent;
    Thread _thread;

    NON_COPYABLE(Timer);
    NON_MOVEABLE(Timer);

  public:
    explicit Timer(DWORD timeout, std::function< void () > f);
    ~Timer();

    void cancel();
  };
}

#endif