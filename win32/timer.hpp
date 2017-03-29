#pragma once
#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <memory>
#include <functional>

#include "win32/synch.hpp"
#include "win32/thread.hpp"

namespace Windows
{
  class Timer
  {
    std::function< void () > _f;
    Synch::Event _cancelEvent;
    Thread _thread;

    Timer(const Timer &o);
    Timer &operator=(const Timer &o);
    Timer(Timer &&o);
    Timer &operator=(Timer &&o);

  public:
    explicit Timer(int timeout, std::function< void () > f);
    ~Timer();

    void cancel();
  };
}

#endif