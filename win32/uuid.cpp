/* win32/uuid.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "win32/uuid.hpp"
#include "util/methodscope.hpp"

using namespace Windows;

Uuid::Uuid()
{
  UuidCreateNil(&_uuid);
  UuidCreate(&_uuid);
}

std::wstring Uuid::value(const std::wstring &sPrefix) const
{
  RPC_WSTR sUuid;

  MethodScope m([&sUuid] () { RpcStringFree(&sUuid); });

#if defined(__GNUC__)
  UuidToString(const_cast< UUID * >(&_uuid),&sUuid);
#else
  UuidToString(&_uuid,&sUuid);
#endif

  return sPrefix + std::wstring(reinterpret_cast< wchar_t * >(sUuid));
}
