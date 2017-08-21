/* xfs/exception.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "xfs/exception.hpp"

using namespace XFS;

Exception::Exception(HRESULT errCode) :
  _errCode(errCode)
{

}

const char *Exception::what() const NOEXCEPT(true)
{
  return "XFS::Exception";
}

bool Exception::operator==(HRESULT errCode) const
{
  return _errCode == errCode;
}
