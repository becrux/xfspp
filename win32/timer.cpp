#include "win32/timer.hpp"
#include "log/log.hpp"

using namespace Windows;

Timer::Timer(int timeout, std::function< void () > f) :
  _thread([this, timeout, f] ()
    {
      ::Log::Method m(__LAMBDA_FUNCSIG__("Timer"),LOG_STRING("timeout = " << timeout));

      if (WaitForSingleObjectEx(_cancelEvent.handle(),timeout,FALSE) == WAIT_TIMEOUT)
        f();
    })
{
  ::Log::Method(__FUNCSIG__,LOG_STRING("timeout = " << timeout));
}

Timer::~Timer()
{
  ::Log::Method m(__FUNCSIG__);

  cancel();
}

void Timer::cancel()
{
  ::Log::Method m(__FUNCSIG__);

  _cancelEvent.set();
}
