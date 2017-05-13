/* tests/win32/shmem.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"

#include "win32/shmem.hpp"

TEST_CASE("Shared memory", "[Win32]")
{
  SECTION("access")
  {
    Windows::SharedMemory< DWORD > sm(L"test_shared_memory");
    REQUIRE(sm);

    HANDLE h = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,L"Local\\test_shared_memory_SHMEM");
    REQUIRE(h != NULL);

    LPVOID p = MapViewOfFileEx(h,FILE_MAP_ALL_ACCESS,0,0,0,NULL);
    REQUIRE(p != NULL);

    UnmapViewOfFile(p);
    CloseHandle(h);

    sm.access([] (DWORD *p)
      {
        *p = 5;
      });

    sm.access([](DWORD *p)
      {
        REQUIRE(*p == 5);
      });
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  return run(argc,argv);
}
