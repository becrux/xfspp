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
#include "util/singleton.hpp"

using namespace Log;

class NullBuffer : public std::streambuf
{
public:
  int overflow(int c) { return c; }
};

std::wstring Logger::getPathFromRegistry()
{
  return Windows::Registry::Key(L"Software\\xfspp",HKEY_LOCAL_MACHINE).value(L"logFileName",L"xfspp_mgr.log");
}

std::ostream &Logger::getFileStreamInstance()
{
  static std::ofstream f(convertTo(getPathFromRegistry()),std::ios::out);

  return f;
}

std::ostream &Logger::getNullStreamInstance()
{
  static NullBuffer nullBuffer;
  static std::ostream nullStream(&nullBuffer);

  return nullStream;
}

bool Logger::isLogEnabled()
{
  CREATE_INSTANCE(Windows::Environment::Manager);
  return INSTANCE(Windows::Environment::Manager).get(L"XFSPP_NO_LOG") != L"1";
}

std::ostream &Logger::streamInstance()
{
  static bool canLog = isLogEnabled();

  return (canLog)? getFileStreamInstance() : getNullStreamInstance();
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
