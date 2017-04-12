/* win32/shmem.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "win32/shmem.hpp"
#include "log/log.hpp"

using namespace Windows;

SharedMemory::SharedMemory(DWORD dwSize) :
  Handle<>(CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,dwSize,L"Global\\XFSPP_XFS_MANAGER_SHMEM")),
  _m(L"XFSPP_XFS_MANAGER_SHMEM_MUTEX")
{
  ::Log::Method m(__FUNCSIG__);

  _ptr = reinterpret_cast< std::uint8_t * >(MapViewOfFileEx(handle(),FILE_MAP_ALL_ACCESS,0,0,0,NULL));
}

SharedMemory::~SharedMemory()
{
  ::Log::Method m(__FUNCSIG__);

  UnmapViewOfFile(_ptr);
}
