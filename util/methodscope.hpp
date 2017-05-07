/* util/methodscope.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __METHODSCOPE_HPP__
#define __METHODSCOPE_HPP__

#include <functional>

#include "util/constraints.hpp"

class MethodScope
{
  std::function< void () > _f;

  NON_COPYABLE(MethodScope);

public:
  explicit MethodScope() {}

  explicit MethodScope(std::function< void () > f) :
    _f(f) { }

  explicit MethodScope(MethodScope &&o) :
    _f(std::move(o._f)) { }

  ~MethodScope()
  {
    if (_f)
      _f();
  }

  MethodScope &operator=(MethodScope &&o)
  {
    _f = std::move(o._f);
    return *this;
  }
};

#endif
