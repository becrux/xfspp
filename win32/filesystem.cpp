/* win32/filesystem.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "win32/filesystem.hpp"
#include "util/memory.hpp"

#include <windows.h>
#include <shlwapi.h>

using namespace Windows::FileSystem;

std::wstring Path::temp()
{
  TCHAR path[MAX_PATH + 1];

  clearMem(path);

  GetTempPath(MAX_PATH,path);

  return std::wstring(path);
}

std::wstring Path::tempFileName(const std::wstring &sPrefix)
{
  TCHAR path[MAX_PATH + 1];

  clearMem(path);

  GetTempFileName(temp().c_str(),sPrefix.c_str(),0,path);

  return std::wstring(path);
}

std::wstring Path::combine(const std::wstring &sRoot, const std::wstring &sPath)
{
  TCHAR path[MAX_PATH + 1];

  clearMem(path);

  PathCombine(path,sRoot.c_str(),sPath.c_str());

  return std::wstring(path);
}
