#pragma once
#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <sstream>
#include <fstream>
#include <string>

#include "win32/synch.hpp"

#define LOG_STRING(...) static_cast< std::ostringstream && >(std::ostringstream() << __VA_ARGS__).str()
#define __LAMBDA_FUNCSIG__(sig) "__LAMBDA__[" ## sig ## "]"

namespace Log
{
  class Logger: public std::ostringstream
  {
  public:
    explicit Logger();
    ~Logger();
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

