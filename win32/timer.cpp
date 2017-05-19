/* win32/timer.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "win32/timer.hpp"
#include "log/log.hpp"

using namespace Windows;

Timer::Timer(DWORD timeout, std::function< void () > f) :
  Handle<>(),
  _thread([this, timeout, f] ()
    {
      ::Log::Method m(__LAMBDA_FUNCSIG__("Timer"),STRING("timeout = " << timeout));

      switch (WaitForSingleObjectEx(_cancelEvent.handle(), timeout, FALSE))
      {
        case WAIT_FAILED:
          throw Exception();

        case WAIT_TIMEOUT:
          f();
          break;

        default:
          break;
      }
    })
{
  ::Log::Method(__SIGNATURE__,STRING("timeout = " << timeout));

  setHandle(_thread.handle(),nullCloseHandle);
}

Timer::~Timer()
{
  ::Log::Method m(__SIGNATURE__);

  cancel();
}

void Timer::cancel()
{
  ::Log::Method m(__SIGNATURE__);

  _cancelEvent.set();
}
