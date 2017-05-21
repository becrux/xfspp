/* util/singleton.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include "util/constraints.hpp"
#include <stdexcept>

template< typename T >
class Singleton
{
  static T *_ptr;
  
  NON_COPYABLE(Singleton);
  NON_MOVEABLE(Singleton);
  
public:
  template< typename... Args >
  static void createInstance(Args&&... args)
  {
    if (_ptr)
      return;

    _ptr = new T(std::forward< Args >(args)...);
  }
  
  static void deleteInstance()
  {
    delete _ptr;
    _ptr = nullptr;
  }

  static bool hasInstance()
  {
    return _ptr;
  }
  
  static T &instance()
  {
    if (!_ptr)
      throw std::runtime_error("Singleton< T >::createInstance missing");
     
    return *_ptr;
  }
  
  Singleton &operator==(const Singleton &) = delete;
  Singleton &operator==(Singleton &&) = delete;
};

template< typename T > T *Singleton< T >::_ptr = nullptr;

#define CREATE_INSTANCE(T, ...) Singleton< T >::createInstance(__VA_ARGS__)
#define DELETE_INSTANCE(T, ...) Singleton< T >::deleteInstance()
#define INSTANCE(T) Singleton< T >::instance()
#define HAS_INSTANCE(T) Singleton< T >::hasInstance()

#endif
