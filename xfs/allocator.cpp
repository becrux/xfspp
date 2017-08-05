/* xfs/allocator.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <algorithm>
#include <iterator>

#include "xfs/allocator.hpp"
#include "xfs/exception.hpp"
#include "util/string.hpp"
#include "cen/320/xfsapi.h"
#include "cen/320/xfsadmin.h"

using namespace XFS;

Allocator::Allocator(const std::shared_ptr< Windows::Library > &cMgrLibrary,
                     VOID *pSource,
                     ULONG iSizeHint) :
  _mgrLibrary(cMgrLibrary),
  _sourceWasNull(pSource == nullptr),
  _source(pSource),
  _headPtr(nullptr),
  _sizeHint(iSizeHint),
  _allocatedSize(0)
{

}

VOID *Allocator::mgrAllocate(ULONG ulSize) const
{
  VOID *res = NULL;

  if (_source)
  {
    checkAndAssert(_mgrLibrary->call< HRESULT >("WFMAllocateMore",ulSize,_source,&res));

    if (!_headPtr)
      _headPtr = res;

    _allocatedSize += ulSize;
  }
  else
  {
    checkAndAssert(_mgrLibrary->call< HRESULT >("WFMAllocateBuffer",ulSize,WFS_MEM_ZEROINIT,&res));

    _source = _headPtr = res;
    _allocatedSize += ulSize;
  }

  if (res != NULL)
    memset(res,0,ulSize);

  return res;
}

VOID *Allocator::allocate(ULONG ulSize) const
{
  VOID *res = NULL;

  if (!_source || !_headPtr)
  {
    ULONG reqSize = std::max(ulSize,_sizeHint);
    res = mgrAllocate(reqSize);
    _allocatedSize = ulSize;

    return res;
  }

  if ((_sizeHint > 0) &&
      _headPtr &&
      ((_allocatedSize + ulSize) <= _sizeHint))
  {
    VOID *newPtr = reinterpret_cast< char * >(_headPtr) + _allocatedSize;
    _allocatedSize += ulSize;
    return (res = newPtr);
  }

  return (res = mgrAllocate(ulSize));
}

CHAR *Allocator::create(const std::string &s) const
{
  CHAR *ptr = createArray< CHAR >(s.size() + 1);
  ::strcpy(ptr,s.c_str());

  return ptr;
}

WCHAR *Allocator::create(const std::wstring &s) const
{
  WCHAR *ptr = createArray< WCHAR >(s.size() + 1);
  ::wcscpy(ptr,s.c_str());

  return ptr;
}

CHAR *Allocator::create(const std::vector< std::string > &vs) const
{
  if (vs.empty())
    return nullptr;

  std::vector< char > buf;

  for (const auto &item : vs)
  {
    if (item.empty())
      continue;

    std::string s(item);

    for (const auto &c : s)
      buf.push_back(c);

    buf.push_back(0);
  }

  buf.push_back(0);

  CHAR *ptr = createArray< CHAR >(buf.size());
  ::memcpy(ptr,buf.data(),buf.size());

  return ptr;
}

CHAR *Allocator::create(const std::vector< std::wstring > &vs) const
{
  std::vector< std::string > ivs;

  std::transform(vs.cbegin(),vs.cend(),std::back_inserter(ivs),[] (const std::wstring &item) { return convertTo(item); });
  return create(ivs);
}
