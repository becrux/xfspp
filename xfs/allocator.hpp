/* xfs/allocator.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __XFS_ALLOCATOR_HPP__
#define __XFS_ALLOCATOR_HPP__

#include <vector>
#include <type_traits>
#include <memory>

#include "util/constraints.hpp"
#include "win32/library.hpp"

namespace XFS
{
  namespace detail
  {
    template< typename T >
    class UniquePtrImpl
    {
      NON_COPYABLE(UniquePtrImpl);

      std::shared_ptr< Windows::Library > _mgrLibrary;

    protected:
      T *_ptr;

    public:
      explicit UniquePtrImpl(const std::shared_ptr< Windows::Library > &cMgrLibrary, T *ptr) :
        _mgrLibrary(cMgrLibrary),
        _ptr(ptr) { }
      explicit UniquePtrImpl(UniquePtrImpl &&o) :
        _mgrLibrary(o._mgrLibrary),
        _ptr(o._ptr)
        {
          o._ptr = nullptr;
        }

      ~UniquePtrImpl()
        {
          if (_ptr)
            _mgrLibrary->call< HRESULT >("WFMFreeBuffer",_ptr);
        }

      UniquePtrImpl &operator=(UniquePtrImpl &&o)
        {
          _mgrLibrary = o._mgrLibrary;
          _ptr = o._ptr;
          o._ptr = nullptr;

          return *this;
        }

      T *get() const { return _ptr; }
    };
  }

  template< typename T >
  class UniquePtr : public XFS::detail::UniquePtrImpl< T >
  {
  public:
    explicit UniquePtr(const std::shared_ptr< Windows::Library > &cMgrLibrary, T *ptr) :
      XFS::detail::UniquePtrImpl< T >(cMgrLibrary,ptr) { }
    explicit UniquePtr(UniquePtr &&o) :
      XFS::detail::UniquePtrImpl< T >(std::move(o)) { }

    T *operator->() { return this->_ptr; }
  };

  template<>
  class UniquePtr< VOID > : public XFS::detail::UniquePtrImpl< VOID >
  {
  public:
    explicit UniquePtr(const std::shared_ptr< Windows::Library > &cMgrLibrary, VOID *ptr) :
      XFS::detail::UniquePtrImpl< VOID >(cMgrLibrary,ptr) { }
    explicit UniquePtr(UniquePtr &&o) :
      XFS::detail::UniquePtrImpl< VOID >(std::move(o)) { }
  };

  class Allocator
  {
    std::shared_ptr< Windows::Library > _mgrLibrary;
    bool _sourceWasNull;
    mutable VOID *_source;
    mutable VOID *_headPtr;
    mutable ULONG _sizeHint;
    mutable ULONG _allocatedSize;

    VOID *mgrAllocate(ULONG ulSize) const;
    VOID *allocate(ULONG ulSize) const;

  public:
    explicit Allocator(const std::shared_ptr< Windows::Library > &cMgrLibrary,
                       VOID *pSource,
                       ULONG iSizeHint = 0);

    VOID *headPtr() const { return (_sourceWasNull)? _source : _headPtr; }

    template< typename T >
    T *create() const
      {
        return reinterpret_cast< T * >(allocate(sizeof(T)));
      }

    template< typename T >
    T *create(T value) const
      {
        VOID *ptr = allocate(sizeof(T));

        *(reinterpret_cast< T * >(ptr)) = value;

        return reinterpret_cast< T * >(ptr);
      }

    template< typename T >
    typename std::enable_if< !std::is_integral< T >::value,T >::type **createArray(int N, bool nullTerminated = false, bool createItems = true) const
      {
        VOID *ptr = allocate(sizeof(T *) * ((nullTerminated)? (N + 1) : N));

        T **dataPtr = reinterpret_cast< T ** >(ptr);

        std::generate_n(dataPtr,N,[this, createItems] () { return (createItems)? reinterpret_cast< T * >(this->allocate(sizeof(T))) : nullptr; });

        if (nullTerminated)
          dataPtr[N] = nullptr;

        return dataPtr;
      }

    template< typename T >
    typename std::enable_if< std::is_integral< T >::value,T >::type *createArray(int N) const
      {
        return reinterpret_cast< T * >(allocate(sizeof(T) * N));
      }

    template< typename C >
    typename std::enable_if< std::is_integral< typename C::value_type >::value,typename C::value_type >::type *createArray(const C &c, bool nullTerminated = false) const
      {
        using T = typename C::value_type;

        T *ptr = reinterpret_cast< T * >(allocate(sizeof(T) * ((nullTerminated)? (c.size() + 1) : c.size())));
        T *ePtr = std::copy(c.cbegin(),c.cend(),ptr);
        if (nullTerminated)
          *ePtr = T();

        return ptr;
      }

    CHAR *create(const std::string &s) const;
    WCHAR *create(const std::wstring &s) const;
    CHAR *create(const std::vector< std::wstring > &vs) const;
    CHAR *create(const std::vector< std::string > &vs) const;

    int allocatedSize() const { return _allocatedSize; }
  };
}

#endif
