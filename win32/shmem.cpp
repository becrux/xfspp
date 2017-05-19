/* win32/shmem.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "win32/shmem.hpp"
#include "util/string.hpp"

using namespace Windows;

BaseRawSharedMemory::BaseRawSharedMemory(DWORD dwSize, const std::wstring &sName) :
  Handle<>(CreateFileMapping(
    INVALID_HANDLE_VALUE,
    NULL,
    PAGE_READWRITE,
    0,
    dwSize,
    (std::wstring(L"Local\\") + sName + std::wstring(L"_SHMEM")).c_str())),
  _m((sName + std::wstring(L"_MUTEX")).c_str()),
  _size(dwSize),
  _ptr(MapViewOfFileEx(handle(),FILE_MAP_ALL_ACCESS,0,0,0,NULL))
{
  if (_ptr == NULL)
    throw Exception();

  ::Log::Method m(__SIGNATURE__,WSTRING(L"sName = " << sName));
}

BaseRawSharedMemory::~BaseRawSharedMemory()
{
  ::Log::Method m(__SIGNATURE__);

  UnmapViewOfFile(_ptr);
}

void BaseRawSharedMemory::access(std::function< void(DWORD, LPVOID) > f)
{
  ::Log::Method m(__SIGNATURE__);

  Synch::Locker< Synch::Mutex > lock(_m);

  f(_size,_ptr);
}

RawSharedMemory::RawSharedMemory(DWORD dwSize,const std::wstring &sName) :
  BaseRawSharedMemory(dwSize,sName)
{
  ::Log::Method m(__SIGNATURE__);
}

RawSharedMemory::~RawSharedMemory()
{
  ::Log::Method m(__SIGNATURE__);
}

void RawSharedMemory::access(std::function< void(DWORD, LPVOID) > f)
{
  ::Log::Method m(__SIGNATURE__);

  BaseRawSharedMemory::access(f);
}
