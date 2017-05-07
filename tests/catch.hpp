#pragma once
#ifndef XFSPP_CATCH_HPP
#define XFSPP_CATCH_HPP

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#define CATCH_CONFIG_RUNNER
#include "catch/catch.hpp"

#include <functional>

#include <windows.h>

int run(int argc, wchar_t const* const* const argv, std::function< void (const std::wstring &) > initLibF = std::function< void (const std::wstring &) >())
{
  SetEnvironmentVariable(L"XFSPP_LOG_ON_CONSOLE",L"1");

  char **utf8Argv = new char *[argc];
  for (int i = 0; i < argc; ++i)
	utf8Argv[i] = nullptr;

  bool nextIsALib = false;
  int idx = 0;
  for (int i = 0; i < argc; ++i)
  {
	if (std::wstring(argv[i]) == L"--lib")
	  nextIsALib = true;
	else if (nextIsALib)
	{
	  nextIsALib = false;
	  if (initLibF)
		initLibF(std::wstring(argv[i]));
	}
	else
	{
      int bufSize = WideCharToMultiByte(CP_UTF8,0,argv[i],-1,NULL,0,NULL,NULL);
      
      utf8Argv[idx] = new char[bufSize];
      
      WideCharToMultiByte(CP_UTF8,0,argv[i],-1,utf8Argv[idx++],bufSize,NULL,NULL);
	}
  }

  int returnCode = Catch::Session().run(idx,utf8Argv);

  for (int i = 0; i < idx; ++i)
    delete [] utf8Argv[i];

  delete [] utf8Argv;

  return returnCode;
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
