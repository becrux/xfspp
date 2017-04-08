#pragma once
#ifndef __METHODSCOPE_HPP__
#define __METHODSCOPE_HPP__

#include <functional>

class MethodScope
{
  std::function< void () > _f;

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
