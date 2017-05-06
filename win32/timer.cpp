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

Timer::Timer(int timeout, std::function< void () > f) :
  Handle<>(NULL,nullCloseHandle),
  _thread([this, timeout, f] ()
    {
      ::Log::Method m(__LAMBDA_FUNCSIG__("Timer"),STRING("timeout = " << timeout));

      if (WaitForSingleObjectEx(_cancelEvent.handle(),timeout,FALSE) == WAIT_TIMEOUT)
        f();
    })
{
  ::Log::Method(__SIGNATURE__,STRING("timeout = " << timeout));

  setHandle(_thread.handle());
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
