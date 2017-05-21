/* tests/catch.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

 #pragma once
#ifndef XFSPP_CATCH_HPP
#define XFSPP_CATCH_HPP

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#define CATCH_CONFIG_RUNNER
#include "catch/catch.hpp"

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <functional>

#include <windows.h>

int run(int argc, wchar_t **argv, std::function< void (const std::wstring &) > initLibF = std::function< void (const std::wstring &) >())
{
  SetEnvironmentVariable(L"XFSPP_NO_LOG",L"1");

  for (int i = 0; i < argc; ++i)
	  if (std::wstring(argv[i]) == L"--lib")
    {
	    if (initLibF)
	      initLibF(std::wstring(argv[i+1]));
      
      std::swap(argv[argc-2],argv[i]);
      std::swap(argv[argc-1],argv[i+1]);
      argc -= 2;
      break;
    }

  return Catch::Session().run(argc,argv);
}

#endif
