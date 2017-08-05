/* log/log.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <fstream>
#include <sstream>
#include <string>

#include <windows.h>

#include "util/string.hpp"
#include "util/constraints.hpp"

#define __LAMBDA_FUNCSIG__(sig) "__LAMBDA__[" sig "]"

#if defined(__GNUC__)
  #define __SIGNATURE__ __PRETTY_FUNCTION__
#else
  #define __SIGNATURE__ __FUNCSIG__
#endif

namespace Log
{
  class Logger: public std::ostringstream
  {
    static std::wstring getPathFromRegistry();

    static std::ostream &getFileStreamInstance();
    static std::ostream &getNullStreamInstance();

    static bool isLogEnabled();

    NON_COPYABLE(Logger);

  public:
    explicit Logger();
    ~Logger();

    static std::ostream &streamInstance();
  };

  class Method
  {
    DWORD _tick;
    std::string _fName;
    std::string _params;

  public:
    explicit Method(const std::string &fName, const std::string &params = std::string());
    ~Method();
  };
}

#endif
