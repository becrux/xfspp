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

Mutex::Mutex() :
  Lockable(CreateMutex(NULL,FALSE,NULL))
{

}

void Mutex::unlock()
{
  ReleaseMutex(handle());
};

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
