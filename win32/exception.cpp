/* win32/exception.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <windows.h>

#include "util/memory.hpp"
#include "util/string.hpp"
#include "win32/exception.hpp"

using namespace Windows;

Exception::Exception() :
  std::system_error(static_cast< int >(GetLastError()),std::system_category(),errorToMsg())
{

}

std::string Exception::errorToMsg()
{
  wchar_t buf[1024];
  
  clearMem(buf);

  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,GetLastError(),MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),buf,1024,NULL);
  
  return convertTo(std::wstring(buf));
}
