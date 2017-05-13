/* util/string.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "util/string.hpp"

#include <windows.h>
#include <shlwapi.h>

std::string convertTo(const std::wstring &s)
{
  int nd = WideCharToMultiByte(CP_UTF8,0,s.c_str(),-1,NULL,0,NULL,NULL);

  char *buf = new char[static_cast< unsigned int >(nd)];
  WideCharToMultiByte(CP_UTF8,0,s.c_str(),-1,buf,nd,NULL,NULL);
  
  std::string res(buf);

  delete [] buf;

  return res;
}

std::wstring convertTo(const std::string &s)
{
  int nd = MultiByteToWideChar(CP_UTF8,0,s.c_str(),-1,NULL,0);

  wchar_t *buf = new wchar_t[static_cast< unsigned int >(nd)];
  MultiByteToWideChar(CP_UTF8,0,s.c_str(),-1,buf,nd);

  std::wstring res(buf);

  delete [] buf;

  return res;
}

int icasecmp(const std::wstring &s1, const std::wstring &s2)
{
  return StrCmpLogicalW(s1.c_str(),s2.c_str());
}
