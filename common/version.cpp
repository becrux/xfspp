/* common/version.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <iomanip>
#include <limits>

#include "common/version.hpp"

using namespace XFS;

Version::Version(WORD wVersion) :
  _major(wVersion & 0xff),
  _minor((wVersion >> 8) & 0xff)
{
  
}

Version::Version(BYTE bMajor, BYTE bMinor) :
  _major(bMajor),
  _minor(bMinor)
{
  
}
  
WORD Version::value() const
{
  return (_minor << 8) | _major;
}

Version Version::min(BYTE bMajor)
{
  return Version(bMajor,std::numeric_limits< BYTE >::min());
}

Version Version::max(BYTE bMajor)
{
  return Version(bMajor,std::numeric_limits< BYTE >::max());
}

std::tuple< Version,Version > Version::split(DWORD dwVersions)
{
  return std::make_tuple< Version,Version >(Version(dwVersions >> 16),Version(dwVersions & 0xffff));
}
    
bool XFS::operator<(const Version &a, const Version &b)
{
  return (a._major < b._major) || ((a._major == b._major) && (a._minor < b._minor));
}

bool XFS::operator==(const Version &a, const Version &b)
{
  return (a._major == b._major) && (a._minor == b._minor);
}

bool XFS::operator<=(const Version &a, const Version &b)
{
  return (a < b) || (a == b);
}

bool XFS::operator!=(const Version &a, const Version &b)
{
  return !(a == b);
}

bool XFS::operator>=(const Version &a, const Version &b)
{
  return !(a < b);
}

bool XFS::operator>(const Version &a, const Version &b)
{
  return !(a <= b);
}

std::ostream &XFS::operator<<(std::ostream &out, const Version &v)
{
  out << v._major << "." << std::setw(2) << std::setfill('0') << v._minor;
  
  return out;
}
