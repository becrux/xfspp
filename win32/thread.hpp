#pragma once
#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include <functional>
#include <memory>

#include "win32/handle.hpp"
#include "win32/synch.hpp"

namespace Windows
{
  class Thread : public Handle
  {
    Synch::Semaphore _startSem;
    std::function< void () > _f;

    static DWORD WINAPI threadProc(LPVOID lpParameter);

  public:
    explicit Thread(std::function< void () > f);
    ~Thread();
  };
}

#endif
