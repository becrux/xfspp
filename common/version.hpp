/* common/version.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __VERSION_HPP__
#define __VERSION_HPP__

#include <iostream>
#include <tuple>

#include <windows.h>

namespace XFS
{
  class Version
  {
    WORD _major;
    WORD _minor;

  public:
    explicit Version(WORD wVersion);
    explicit Version(BYTE bMajor, BYTE bMinor);
    
    WORD value() const;
    
    static std::tuple< Version,Version > split(DWORD dwVersions);
    static Version min(BYTE bMajor);
    static Version max(BYTE bMajor);
    
    friend bool operator<(const Version &a, const Version &b);
    friend bool operator<=(const Version &a, const Version &b);
    friend bool operator==(const Version &a, const Version &b);
    friend bool operator!=(const Version &a, const Version &b);
    friend bool operator>=(const Version &a, const Version &b);
    friend bool operator>(const Version &a, const Version &b);
    friend std::ostream &operator<<(std::ostream &out, const Version &v);
  };

  bool operator<(const Version &a,const Version &b);
  bool operator<=(const Version &a,const Version &b);
  bool operator==(const Version &a,const Version &b);
  bool operator!=(const Version &a,const Version &b);
  bool operator>=(const Version &a,const Version &b);
  bool operator>(const Version &a,const Version &b);
  std::ostream &operator<<(std::ostream &out,const Version &v);
}

#endif

