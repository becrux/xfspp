#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

template< typename T >
inline void clearMem(T &var)
{
  ::memset(&var,0,sizeof(T));
}

#endif
