/* util/operators.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef __OPERATORS_HPP__
#define __OPERATORS_HPP__

template< typename T >
struct EqualComparable
{
  friend bool operator!=(const T &a,const T &b) { return !(a == b); }
};

template< typename T >
struct Comparable : public EqualComparable< T >
{
  friend bool operator<=(const T &a, const T &b) { return (a < b) || (a == b); }
  friend bool operator>(const T &a,const T &b) { return !(a <= b); }
  friend bool operator>=(const T &a,const T &b) { return !(a < b); }
};

#endif
