/* win32/environment.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <utility>
#include <memory>

#include <windows.h>

#include "win32/environment.hpp"
#include "win32/exception.hpp"

using namespace Windows::Environment;

Manager::Manager()
{
  wchar_t *p = GetEnvironmentStrings();
  if (p == NULL)
    throw Windows::Exception();

  std::shared_ptr< wchar_t > pEnv(p,FreeEnvironmentStrings);

  std::wstring currentKey;
  std::wstring currentValue;
  bool isKey = true;

  while ((*p != L'\0') || (*(p+1) != L'\0'))
  {
    if (*p == L'\0')
    {
      if (!currentKey.empty() && !currentValue.empty())
        _vars.insert({ currentKey,currentValue });
      currentKey.clear();
      currentValue.clear();
      isKey = true;
    }
    else if (isKey)
    {
      if (*p == L'=')
        isKey = false;
      else
        currentKey += *p;
    }
    else
      currentValue += *p;

    ++p;
  }

  if (!currentKey.empty() && !currentValue.empty())
    _vars.insert({ currentKey,currentValue });
}

std::wstring Manager::get(const std::wstring &key, const std::wstring &sDefault) const
{
  auto it = _vars.find(key);

  return (it != _vars.end())? it->second : sDefault;
}

bool Manager::has(const std::wstring &key) const
{
  return _vars.find(key) != _vars.cend();
}

void Manager::set(const std::wstring &key, const std::wstring &value)
{
  std::wstring k(key);
  std::wstring v(value);
  if (SetEnvironmentVariable(k.c_str(),v.c_str()))
    _vars[key] = value;
  else
    throw Exception();
}

void Manager::remove(const std::wstring &key)
{
  std::wstring k(key);
  if (SetEnvironmentVariable(k.c_str(),NULL))
    _vars.erase(key);
  else
    throw Exception();
}

std::list< std::wstring > Manager::keys() const
{
  std::list< std::wstring > l;

  for (const std::pair< std::wstring,std::wstring > &item : _vars)
    l.push_back(item.first);

  return l;
}

std::ostream &Windows::Environment::operator<<(std::ostream &out, const Windows::Environment::Manager &m)
{
  for (const auto &item : m._vars)
    out << convertTo(item.first) << "=" << convertTo(item.second) << std::endl;

  return out;
}
