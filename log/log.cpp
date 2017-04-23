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
#include "spdlog/spdlog.h"

using namespace Log;

extern spdlog::logger *logger;

Logger::Logger()
{

}

Logger::~Logger()
{
  SYSTEMTIME st;
  GetLocalTime(&st);

  logger->debug("{0}-{1}-{2}T{3}:{4}:{5}.{6}\t{7:#06x}\t{8:#06x}\t{9}",
    st.wYear,st.wMonth,st.wDay,
    st.wHour,st.wMinute,st.wSecond,st.wMilliseconds,
    GetCurrentProcessId(),GetCurrentThreadId(),
    str());
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
