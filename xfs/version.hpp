/* xfs/version.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __XFS_VERSION_HPP__
#define __XFS_VERSION_HPP__

#include <iostream>
#include <tuple>

#include <windows.h>

#include "util/operators.hpp"

namespace XFS
{
  class Version : private Comparable< Version >
  {
    WORD _major;
    WORD _minor;

  public:
    explicit Version(WORD wVersion);
    explicit Version(BYTE bMajor, BYTE bMinor);

    WORD value() const;

    WORD major() const;
    WORD minor() const;

    static Version min(BYTE bMajor);
    static Version max(BYTE bMajor);

    bool operator<(const Version &o) const;
    bool operator==(const Version &o) const;
  };

  class VersionRange : private EqualComparable< VersionRange >
  {
    Version _start;
    Version _end;

  public:
    explicit VersionRange(DWORD dwVersion);
    explicit VersionRange(const Version &vStart, const Version &vEnd);

    Version start() const;
    Version end() const;

    DWORD value() const;

    bool contains(const Version &v) const;

    bool operator==(const VersionRange &o) const;
  };

  std::ostream &operator<<(std::ostream &out,const Version &v);
  std::ostream &operator<<(std::ostream &out,const VersionRange &v);
}

#endif

