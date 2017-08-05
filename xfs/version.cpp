/* xfs/version.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <iomanip>
#include <limits>

#include "xfs/version.hpp"

using namespace XFS;

Version::Version(WORD wVersion) :
  _major(static_cast< WORD >(wVersion & 0xff)),
  _minor(static_cast< WORD >((wVersion >> 8) & 0xff))
{

}

Version::Version(BYTE bMajor, BYTE bMinor) :
  _major(bMajor),
  _minor(bMinor)
{

}

WORD Version::value() const
{
  return static_cast< WORD >((minor() << 8) | major());
}

WORD Version::major() const
{
  return _major;
}

WORD Version::minor() const
{
  return _minor;
}

Version Version::min(BYTE bMajor)
{
  return Version(bMajor,std::numeric_limits< BYTE >::min());
}

Version Version::max(BYTE bMajor)
{
  return Version(bMajor,std::numeric_limits< BYTE >::max());
}

bool Version::operator<(const Version &o) const
{
  return (major() < o.major()) || ((major() == o.major()) && (minor() < o.minor()));
}

bool Version::operator==(const Version &o) const
{
  return (major() == o.major()) && (minor() == o.minor());
}

std::ostream &XFS::operator<<(std::ostream &out, const Version &v)
{
  out << v.major() << "." << std::setw(2) << std::setfill('0') << v.minor();

  return out;
}

VersionRange::VersionRange(DWORD dwVersion) :
  _start(dwVersion >> 16),
  _end(dwVersion & 0xffff)
{

}

VersionRange::VersionRange(const Version &vStart, const Version &vEnd) :
  _start(vStart),
  _end(vEnd)
{

}

Version VersionRange::start() const
{
  return _start;
}

Version VersionRange::end() const
{
  return _end;
}

DWORD VersionRange::value() const
{
  return static_cast< DWORD >((start().value() << 16) | end().value());
}

bool VersionRange::contains(const Version &v) const
{
  return (v >= start()) && (v <= end());
}

bool VersionRange::operator==(const VersionRange &o) const
{
  return (start() == o.start()) && (end() == o.end());
}

std::ostream &XFS::operator<<(std::ostream &out,const VersionRange &v)
{
  out << "[" << v.start() << " - " << v.end() << "]";

  return out;
}
