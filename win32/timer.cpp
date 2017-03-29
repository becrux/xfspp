#include "win32/timer.hpp"

using namespace Windows;

Timer::Timer(int timeout, std::function< void () > f) :
  _thread([this, timeout, f] ()
    {
      if (WaitForSingleObjectEx(_cancelEvent.handle(),timeout,FALSE) == WAIT_TIMEOUT)
        f();
    })
{

}

Timer::~Timer()
{
  _cancelEvent.set();
}

void Timer::cancel()
{
  _cancelEvent.set();
}
