/* util/string.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "util/string.hpp"
#include "win32/exception.hpp"

#include <windows.h>
#include <shlwapi.h>

std::string convertTo(const std::wstring &s)
{
  int nd = WideCharToMultiByte(CP_UTF8,0,s.c_str(),-1,NULL,0,NULL,NULL);
  if (!nd)
    throw Windows::Exception();

  char *buf = new char[static_cast< unsigned int >(nd)];
  if (!WideCharToMultiByte(CP_UTF8,0,s.c_str(),-1,buf,nd,NULL,NULL))
    throw Windows::Exception();

  std::string res(buf);

  delete [] buf;

  return res;
}

std::wstring convertTo(const std::string &s)
{
  int nd = MultiByteToWideChar(CP_UTF8,0,s.c_str(),-1,NULL,0);
  if (!nd)
    throw Windows::Exception();

  wchar_t *buf = new wchar_t[static_cast< unsigned int >(nd)];
  if (!MultiByteToWideChar(CP_UTF8,0,s.c_str(),-1,buf,nd))
    throw Windows::Exception();

  std::wstring res(buf);

  delete [] buf;

  return res;
}

int icasecmp(const std::wstring &s1, const std::wstring &s2)
{
  return StrCmpLogicalW(s1.c_str(),s2.c_str());
}
