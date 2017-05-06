/* win32/uuid.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __UUID_HPP__
#define __UUID_HPP__

#include <functional>
#include <string>

#include <windows.h>
#include <rpc.h>

namespace Windows
{
  class Uuid
  {
    ::UUID _uuid;

  public:
    explicit Uuid();

    std::wstring value(const std::wstring &sPrefix = std::wstring()) const;
  };
}

#endif
