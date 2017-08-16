/* xfs/exception.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __XFS_EXCEPTION_HPP__
#define __XFS_EXCEPTION_HPP__

#include <exception>

#include "cen/320/xfsapi.h"

#if defined(_MSC_VER)
  #if _MSC_VER <= 1800
    #define NOEXCEPT
  #else
    #define NOEXCEPT noexcept
  #endif
#else
  #define NOEXCEPT noexcept
#endif

namespace XFS
{
  class Exception : public std::exception
  {
    HRESULT _errCode;

  public:
    explicit Exception(HRESULT errCode);
	
    const char *what() const NOEXCEPT;
    
    bool operator==(HRESULT errCode) const;
  };
  
  inline void checkAndAssert(HRESULT errCode)
  {
    if (errCode != WFS_SUCCESS)
      throw Exception(errCode);
  }

  inline void checkAndAssert(HRESULT errCode, HRESULT ignoreCode)
  {
    if ((errCode != WFS_SUCCESS) && (errCode != ignoreCode))
      throw Exception(errCode);
  }
}

#endif
