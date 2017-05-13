/* log/log.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <iostream>
#include <iomanip>
#include <fstream>

#include "log/log.hpp"
#include "win32/registry.hpp"
#include "win32/environment.hpp"

using namespace Log;

std::string Logger::getPathFromRegistry()
{
  return Windows::Registry::Key(L"Software\\xfspp",HKEY_LOCAL_MACHINE).value(L"logFileName","xfspp_mgr.log");
}

std::ostream &Logger::getFileStreamInstance()
{
  static std::ofstream f(getPathFromRegistry(),std::ios::out);

  return f;
}

std::ostream &Logger::getConsoleStreamInstance()
{
  return std::cout;
}

bool Logger::isLogOnConsole()
{
  return Windows::Environment::Manager::instance().get(L"XFSPP_LOG_ON_CONSOLE") == L"1";
}

std::ostream &Logger::streamInstance()
{
  static bool onConsole = isLogOnConsole();

  return (onConsole)? getConsoleStreamInstance() : getFileStreamInstance();
}

Logger::Logger()
{

}

Logger::~Logger()
{
  SYSTEMTIME st;
  GetLocalTime(&st);

  streamInstance() << 
    st.wYear << "-" <<
    std::setw(2) << std::setfill('0') << st.wMonth << "-" <<
    std::setw(2) << std::setfill('0') << st.wDay << "-" <<
    "T" <<
    std::setw(2) << std::setfill('0') << st.wHour << ":" <<
    std::setw(2) << std::setfill('0') << st.wMinute << ":" <<
    std::setw(2) << std::setfill('0') << st.wSecond << "." <<
    st.wMilliseconds << "\t" <<
    std::setw(6) << std::setfill('0') << GetCurrentProcessId() << "\t" <<
    std::setw(6) << std::setfill('0') << GetCurrentThreadId() << "\t" <<
    str() << std::endl;
}

Method::Method(const std::string &fName, const std::string &params) :
  _tick(GetTickCount()),
  _fName(fName),
  _params(params)
{
  Logger() << "ENTER\t" << _fName << "\t" << _params;
}

Method::~Method()
{
  Logger() << "EXIT\t" << _fName << "\t" << _params << "\telapsed = " << (GetTickCount() - _tick);
}
