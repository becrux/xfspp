#include "win32/handle.hpp"

using namespace Windows;

Handle::Handle(HANDLE h, int (_stdcall *closeF)(HANDLE)) :
  _h(h),
  _closeF(closeF)
{

}

Handle::Handle(Handle &&o) :
  _h(o._h),
  _closeF(o._closeF)
{
  o._h = NULL;
}

Handle::~Handle()
{
  if (_h != NULL)
  {
    _closeF(_h);
    _h = NULL;
  }
}

Handle &Handle::operator=(Handle &&o)
{
  _h = o._h;
  _closeF = o._closeF;
  o._h = NULL;

  return *this;
}
 
HANDLE Handle::handle() const
{
  return _h;
}

void Handle::setHandle(HANDLE h)
{
  _h = h;
}
