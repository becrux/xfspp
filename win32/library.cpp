/* win32/library.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "win32/library.hpp"
#include "log/log.hpp"

using namespace Windows;

Library::Library(const std::wstring &sLibPath) :
  Handle< HMODULE >(LoadLibraryEx(sLibPath.c_str(),NULL,0),FreeLibrary)
{
  ::Log::Method m(__SIGNATURE__);
}

Library::~Library()
{
  ::Log::Method m(__SIGNATURE__);
}
