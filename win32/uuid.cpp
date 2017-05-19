/* win32/uuid.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "win32/uuid.hpp"
#include "util/methodscope.hpp"
#include "win32/exception.hpp"

using namespace Windows;

Uuid::Uuid()
{
  RPC_STATUS res;

  if ((res = UuidCreateNil(&_uuid)) != RPC_S_OK)
  {
    SetLastError(static_cast< DWORD >(res));
    throw Exception();
  }

  if ((res = UuidCreate(&_uuid)) != RPC_S_OK)
  {
    SetLastError(static_cast< DWORD >(res));
    throw Exception();
  }
}

std::wstring Uuid::value(const std::wstring &sPrefix) const
{
  RPC_WSTR sUuid = NULL;

  MethodScope m([&sUuid] () { RpcStringFree(&sUuid); });

  RPC_STATUS res;
  if ((res =

  #if defined(__GNUC__)
    UuidToString(const_cast<UUID *>(&_uuid), &sUuid)
  #else
    UuidToString(&_uuid, &sUuid)
  #endif
    ) != RPC_S_OK)
  {
    SetLastError(static_cast< DWORD >(res));
    throw Exception();
  }

  return sPrefix + std::wstring(reinterpret_cast< wchar_t * >(sUuid));
}
