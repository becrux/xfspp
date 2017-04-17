/* win32/synch.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "win32/synch.hpp"

using namespace Windows::Synch;

Lockable::Lockable(HANDLE h) :
  Handle(h)
{

}

void Lockable::lock()
{
  WaitForSingleObjectEx(handle(),INFINITE,FALSE);
}

Mutex::Mutex(const std::wstring &sName) :
  Lockable(CreateMutex(NULL,FALSE,(sName.empty())? NULL : (std::wstring(L"Global\\") + sName).c_str()))
{

}

void Mutex::unlock()
{
  ReleaseMutex(handle());
}

Semaphore::Semaphore(LONG start, LONG max) :
  Lockable(CreateSemaphore(NULL,start,max,NULL))
{

}

void Semaphore::unlock()
{
  ReleaseSemaphore(handle(),1,NULL);
}

Event::Event() :
  Handle(CreateEvent(NULL,TRUE,FALSE,NULL))
{

}

void Event::waitFor()
{
  WaitForSingleObjectEx(handle(),INFINITE,FALSE);
}

void Event::set()
{
  SetEvent(handle());
}
