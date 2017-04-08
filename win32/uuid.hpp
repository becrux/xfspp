#pragma once
#ifndef __UUID_HPP__
#define __UUID_HPP__

#include <functional>
#include <string>

#include <windows.h>

namespace Windows
{
  class Uuid
  {
    ::UUID _uuid;

  public:
    explicit Uuid();

    std::wstring value() const;
  };
}

#endif
