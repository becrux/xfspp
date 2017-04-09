/* util/memory.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

template< typename T >
inline void clearMem(T &var)
{
  ::memset(&var,0,sizeof(T));
}

#endif
