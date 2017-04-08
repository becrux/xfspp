#include "win32/uuid.hpp"
#include "util/methodscope.hpp"

using namespace Windows;

Uuid::Uuid()
{
  UuidCreateNil(&_uuid);
  UuidCreate(&_uuid);
}

std::wstring Uuid::value() const
{
  RPC_WSTR sUuid;

  MethodScope m([&sUuid] () { RpcStringFree(&sUuid); });

  UuidToString(&_uuid,&sUuid);
  
  return std::wstring(reinterpret_cast< wchar_t * >(sUuid));
}
