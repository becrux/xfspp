/* win32/shmem.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "win32/shmem.hpp"

using namespace Windows;

RawSharedMemory::RawSharedMemory(DWORD dwSize) :
  Handle<>(CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,dwSize,value(L"Global\\XFSPP_XFS_MANAGER_SHMEM_").c_str())),
  _m(value(L"Global\\XFSPP_XFS_MANAGER_SHMEM_MUTEX_")),
  _ptr(MapViewOfFileEx(handle(),FILE_MAP_ALL_ACCESS,0,0,0,NULL))
{
  ::Log::Method m(__SIGNATURE__);
}

RawSharedMemory::~RawSharedMemory()
{
  ::Log::Method m(__SIGNATURE__);

  UnmapViewOfFile(_ptr);
}

void RawSharedMemory::access(std::function< void(LPVOID) > f)
{
  ::Log::Method m(__SIGNATURE__);

  Synch::Locker< Synch::Mutex > lock(_m);

  f(_ptr);
}
