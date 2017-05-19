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
  if (WaitForSingleObjectEx(handle(),INFINITE,FALSE) == WAIT_FAILED)
    throw Exception();
}

Mutex::Mutex(const std::wstring &sName) :
  Lockable(CreateMutex(NULL,FALSE,(sName.empty())? NULL : (std::wstring(L"Local\\") + sName).c_str()))
{

}

void Mutex::unlock()
{
  if (!ReleaseMutex(handle()))
    throw Exception();
}

Semaphore::Semaphore(LONG start, LONG max, const std::wstring &sName) :
  Handle<>(CreateSemaphore(NULL,start,max,(sName.empty())? NULL : (std::wstring(L"Local\\") + sName).c_str()))
{

}

void Semaphore::acquire()
{
  if (WaitForSingleObjectEx(handle(),INFINITE,FALSE) == WAIT_FAILED)
    throw Exception();
}

void Semaphore::release()
{
  if (!ReleaseSemaphore(handle(),1,NULL))
    throw Exception();
}

Event::Event(const std::wstring &sName) :
  Handle(CreateEvent(NULL,TRUE,FALSE,(sName.empty())? NULL : (std::wstring(L"Local\\") + sName).c_str()))
{

}

void Event::waitFor()
{
  if (WaitForSingleObjectEx(handle(),INFINITE,FALSE) == WAIT_FAILED)
    throw Exception();
}

void Event::set()
{
  if (!SetEvent(handle()))
    throw Exception();
}
