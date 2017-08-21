/* win32/thread.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "win32/thread.hpp"
#include "log/log.hpp"

using namespace Windows;

Thread::Thread(std::function< void () > f) :
  Handle<>(),
  _joined(false),
  _f(f)
{
  ::Log::Method m(__SIGNATURE__);

  setHandle(CreateThread(NULL,0,threadProc,reinterpret_cast< LPVOID >(this),0,NULL));
}

Thread::Thread(Thread &&o) :
  Handle<>(std::move(o)),
  _joined(o._joined),
  _f(std::move(o._f))
{

}

Thread::~Thread()
{
  ::Log::Method m(__SIGNATURE__);

  doJoin(false);
}

Thread &Thread::operator=(Thread &&o)
{
  Handle<>::operator=(std::move(o));
  _joined = o._joined;
  _f = std::move(o._f);

  return *this;
}

void Thread::doJoin(bool rethrow)
{
  ::Log::Method m(__SIGNATURE__);

  if (_joined)
    return;

  if (handle())
  {
    if ((WaitForSingleObjectEx(handle(),INFINITE,FALSE) == WAIT_FAILED) && rethrow)
      throw Exception();
  }

  _joined = true;

  if (_eptr && rethrow)
    std::rethrow_exception(_eptr);
}

void Thread::join()
{
  doJoin(true);
}

DWORD WINAPI Thread::threadProc(LPVOID lpParameter)
{
  ::Log::Method m(__SIGNATURE__);

  Thread *me = reinterpret_cast< Thread * >(lpParameter);

  try
  {
    me->_f();
  }
  catch (...)
  {
    me->_eptr = std::current_exception();
  }

  return 0;
}
