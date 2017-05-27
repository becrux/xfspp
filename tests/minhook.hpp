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

#define MOCK_API_NOWIDE_FUNCTION(retType, retValue, funcName, ...) \
  retType WINAPI Mock##funcName(__VA_ARGS__) \
  { \
    return retValue; \
  }

#define MOCK_API_FUNCTION(retType, retValue, funcName, ...) \
  retType WINAPI Mock##funcName##W(__VA_ARGS__) \
  { \
    return retValue; \
  }

#define CREATE_NOWIDE_HOOK(funcName) MH_CreateHook(reinterpret_cast< LPVOID >(&funcName),reinterpret_cast< LPVOID >(&Mock##funcName),NULL);
#define CREATE_NOWIDE_WITH_PREV_HOOK(funcName, prevFunc) MH_CreateHook(reinterpret_cast< LPVOID >(&funcName),reinterpret_cast< LPVOID >(&Mock##funcName),reinterpret_cast< LPVOID * >(&prevFunc));
#define CREATE_HOOK(funcName) MH_CreateHook(reinterpret_cast< LPVOID >(&funcName##W),reinterpret_cast< LPVOID >(&Mock##funcName##W),NULL);
#define CREATE_WITH_PREV_HOOK(funcName, prevFunc) MH_CreateHook(reinterpret_cast< LPVOID >(&funcName##W),reinterpret_cast< LPVOID >(&Mock##funcName##W),reinterpret_cast< LPVOID * >(&prevFunc##W));

#define RUN_WITH_NOWIDE_HOOK(funcName, code) \
  { \
    MH_EnableHook(reinterpret_cast< LPVOID >(&funcName)); \
    code \
    MH_DisableHook(reinterpret_cast< LPVOID >(&funcName)); \
  } \
  while(false)

#define RUN_WITH_HOOK(funcName, code) \
  { \
    MH_EnableHook(reinterpret_cast< LPVOID >(&funcName##W)); \
    code \
    MH_DisableHook(reinterpret_cast< LPVOID >(&funcName##W)); \
  } \
  while(false)

#define RUN_WITH_MINHOOK(code) \
  { \
    MH_Initialize(); \
\
    code \
\
    MH_Uninitialize(); \
  } \
  while(false)

#endif
