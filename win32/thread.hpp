#pragma once
#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include <functional>

#include "win32/handle.hpp"

namespace Windows
{
  class Thread : public Handle<>
  {
    bool _joined;
    std::function< void () > _f;

    static DWORD WINAPI threadProc(LPVOID lpParameter);

  public:
    explicit Thread(std::function< void () > f);
    ~Thread();

    void join();
  };
}

#endif
