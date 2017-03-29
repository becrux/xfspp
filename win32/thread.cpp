#include "win32/thread.hpp"

using namespace Windows;

Thread::Thread(std::function< void () > f) :
  _startSem(0,1),
  _f(f),
  Handle()
{
  setHandle(CreateThread(NULL,0,threadProc,reinterpret_cast< LPVOID >(this),0,NULL));

  _startSem.lock();
}

Thread::~Thread()
{
  if (handle())
    WaitForSingleObjectEx(handle(),INFINITE,FALSE);
}

DWORD WINAPI Thread::threadProc(LPVOID lpParameter)
{
  Thread *me = reinterpret_cast< Thread * >(lpParameter);

  std::function< void () > f = me->_f;
  me->_startSem.unlock();

  f();

  return 0;
}
