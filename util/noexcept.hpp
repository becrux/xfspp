/* util/noexcept.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __UTIL_NOEXCEPT_HPP__
#define __UTIL_NOEXCEPT_HPP__

#if defined(_MSC_VER)
  #if _MSC_VER <= 1800
    #define NOEXCEPT(arg)
  #else
    #define NOEXCEPT(arg) noexcept(arg)
  #endif
#else
  #define NOEXCEPT(arg) noexcept(arg)
#endif

#endif