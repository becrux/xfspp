#include "win32/thread.hpp"
#include "log/log.hpp"

using namespace Windows;

Thread::Thread(std::function< void () > f) :
  Handle(),
  _joined(false),
  _f(f)
{
  ::Log::Method m(__FUNCSIG__);

  setHandle(CreateThread(NULL,0,threadProc,reinterpret_cast< LPVOID >(this),0,NULL));
}

Thread::~Thread()
{
  ::Log::Method m(__FUNCSIG__);

  join();
}

void Thread::join()
{
  ::Log::Method m(__FUNCSIG__);

  if (_joined)
    return;

  if (handle())
    WaitForSingleObjectEx(handle(),INFINITE,FALSE);

  _joined = true;
}

DWORD WINAPI Thread::threadProc(LPVOID lpParameter)
{
  ::Log::Method m(__FUNCSIG__);

  reinterpret_cast< Thread * >(lpParameter)->_f();

  return 0;
}
