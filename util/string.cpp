/* util/string.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "util/string.hpp"

#include <windows.h>

std::string convertTo(const std::wstring &s)
{
  size_t sz = s.length();
  int nd = WideCharToMultiByte(CP_UTF8,0,s.c_str(),sz,NULL,0,NULL,NULL);
  
  char *buf = new char[nd];
  WideCharToMultiByte(CP_UTF8,0,s.c_str(),sz,buf,nd,NULL,NULL);
  
  std::string res(buf);
  
  delete [] buf;
  
  return res;
}

std::wstring convertTo(const std::string &s)
{
  size_t sz = s.length();
  int nd = MultiByteToWideChar(CP_UTF8,0,s.c_str(),sz,NULL,0);
  
  wchar_t *buf = new wchar_t[nd];
  MultiByteToWideChar(CP_UTF8,0,s.c_str(),sz,buf,nd);
  
  std::wstring res(buf);
  
  delete [] buf;
  
  return res;
}
