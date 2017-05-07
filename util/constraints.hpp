/* util/constraints.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __CONSTRAINTS_HPP__
#define __CONSTRAINTS_HPP__

#define NON_COPYABLE(T) \
  T(const T &); \
  T &operator=(const T &)

#define NON_MOVEABLE(T) \
  T(T &&); \
  T &operator=(T &&)

#endif
