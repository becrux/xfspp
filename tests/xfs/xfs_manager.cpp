/* tests/xfs/version.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"

#include "xfs/version.hpp"
#include "win32/registry.hpp"
#include "win32/msgwnd.hpp"

#include <memory>

namespace
{
  Windows::MsgWnd *wnd = nullptr;
}

TEST_CASE("XFS Manager", "[XFS]")
{
  SECTION("WFPOpen")
  {
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  if (argc <= 1)
    return -1;

  std::unique_ptr< Windows::MsgWnd > w(std::make_unique< Windows::MsgWnd >(GetModuleHandle(NULL),
    [] (UINT msgCode, WPARAM wParam, LPARAM lParam)
      {
        
      }));
  wnd = w.get();
  
  return run(argc,argv,
    [] (const std::wstring &libArg)
      {
        Windows::Registry::Key k(L"Software\\XFS\\XFS_MANAGER");
        k.setValue(L"dllName",libArg);

        Windows::Registry::Key k1(L".DEFAULT\\XFS\\LOGICAL_SERVICES\\TEST_MGR",HKEY_USERS);
        k1.setValue(L"provider",L"TEST_MGR_SP");
        k1.setValue(L"class",L"TEST");
        
        Windows::Registry::Key k2(L"SOFTWARE\\XFS\\SERVICE_PROVIDERS\\TEST_MGR_SP",HKEY_LOCAL_MACHINE);
        k2.setValue(L"dllname",L"TEST_MGR_SP");
        k2.setValue(L"vendor_name",L"BeCrux");
        k2.setValue(L"version",L"3.20");
      });
}
