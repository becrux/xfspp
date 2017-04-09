#include <iostream>
#include <iomanip>
#include <fstream>

#include "log/log.hpp"
#include "win32/synch.hpp"

using namespace Log;

Windows::Synch::Mutex _mutex;
std::ofstream _f("C:\\xfs\\build\\out.txt",std::ios::out);

Logger::Logger()
{

}

Logger::~Logger()
{
  Windows::Synch::Locker< Windows::Synch::Mutex > lock(_mutex);

  SYSTEMTIME st;
  GetLocalTime(&st);

  _f <<
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
