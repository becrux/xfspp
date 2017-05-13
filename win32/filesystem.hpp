/* win32/filesystem.hpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __FILESYSTEM_HPP__
#define __FILESYSTEM_HPP__

#include <string>

namespace Windows
{
  namespace FileSystem
  {
    namespace Path
    {
      std::wstring temp();
      std::wstring tempFileName(const std::wstring &sPrefix = std::wstring());
      
      std::wstring combine(const std::wstring &sRoot, const std::wstring &sPath);
    }
  }
}

#endif
