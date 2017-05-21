/* tests/minhook.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

 #pragma once
#ifndef XFSPP_MINHOOK_HPP
#define XFSPP_MINHOOK_HPP

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#include "tests/minhook/include/minhook.h"

#define MOCK_API_FUNCTION(retType, funcName, ...) \
  retType WINAPI Mock##funcName##W(__VA_ARGS__) \
  { \
    return ERROR_ACCESS_DENIED; \
  }

#define CREATE_HOOK(funcName) MH_CreateHook(&funcName##W,&Mock##funcName##W,NULL);

#define RUN_WITH_HOOK(funcName, code) \
  { \
    MH_EnableHook(&funcName##W); \
    code \
    MH_DisableHook(&funcName##W); \
  } \
  while(false)

#endif
