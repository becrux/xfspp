/* util/string.hpp
*
* Copyright (C) 2007 Antonio Di Monaco
*
* This software may be modified and distributed under the terms
* of the MIT license.  See the LICENSE file for details.
*/

#pragma once
#ifndef __UTIL_STRING_HPP__
#define __UTIL_STRING_HPP__

#include <sstream>
#include <string>

#define STRING(...) static_cast< std::ostringstream && >(std::ostringstream() << __VA_ARGS__).str()

std::string convertTo(const std::wstring &s);
std::wstring convertTo(const std::string &s);

#define WSTRING(...) convertTo(static_cast< std::wostringstream && >(std::wostringstream() << __VA_ARGS__).str())

int icasecmp(const std::wstring &s1, const std::wstring &s2);

#endif
