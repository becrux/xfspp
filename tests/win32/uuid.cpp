/* tests/win32/uuid.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "tests/catch.hpp"
#include "tests/minhook.hpp"

#include "win32/uuid.hpp"
#include "win32/exception.hpp"

namespace
{
  MOCK_API_NOWIDE_FUNCTION(RPC_STATUS,RPC_S_CALL_FAILED,UuidCreateNil,UUID __RPC_FAR *)
  MOCK_API_NOWIDE_FUNCTION(RPC_STATUS,RPC_S_UUID_NO_ADDRESS,UuidCreate,UUID __RPC_FAR *)
  MOCK_API_FUNCTION(RPC_STATUS,RPC_S_OUT_OF_MEMORY,UuidToString,const UUID __RPC_FAR *,RPC_CSTR __RPC_FAR *)
}

TEST_CASE("UUID", "[Win32]")
{
  SECTION("generate")
  {
    Windows::Uuid u;

    REQUIRE(!u.value().empty());
  }

  SECTION("failure")
  {
    RUN_WITH_NOWIDE_HOOK(UuidCreateNil,
      {
        REQUIRE_THROWS_AS(Windows::Uuid(),Windows::Exception);
	  });

    RUN_WITH_NOWIDE_HOOK(UuidCreate,
      {
        REQUIRE_THROWS_AS(Windows::Uuid(),Windows::Exception);
	  });

    RUN_WITH_HOOK(UuidToString,
      {
        REQUIRE_THROWS_AS(Windows::Uuid().value(),Windows::Exception);
	  });
  }
}

extern "C" int wmain(int argc, wchar_t **argv, wchar_t **)
{
  int err;
  RUN_WITH_MINHOOK(
    {
      CREATE_NOWIDE_HOOK(UuidCreateNil);
      CREATE_NOWIDE_HOOK(UuidCreate);
      CREATE_HOOK(UuidToString);
      
      err = run(argc,argv);
    });
  
  return err;
}

