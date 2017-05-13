/* util/memory.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include <cstdint>
#include <windows.h>

template< typename T >
inline void clearMem(T &var)
{
  SecureZeroMemory(&var,sizeof(T));
}

template< typename T, size_t N >
inline void clearMem(T (&arr)[N])
{
  SecureZeroMemory(arr,sizeof(T) * N);
}

template< typename T >
inline void copyMem(T &dst, const std::uint8_t *src)
{
  ::memcpy(&dst,src,sizeof(T));
}

template< typename T >
inline void copyMem(std::uint8_t *dst, const T &src)
{
  ::memcpy(dst,&src,sizeof(T));
}

#endif
