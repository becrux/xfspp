ADD_XFSPP_TEST(tests_mgr_startup
  SOURCES
    startup.cpp
    ../../win32/library.cpp
    ../../win32/synch.cpp
    ../../win32/registry.cpp
    ../../win32/environment.cpp
    ../../win32/exception.cpp
    ../../log/log.cpp
    ../../xfs/version.cpp
    ../../util/string.cpp

  LIBS
    shlwapi

  DEPS
    xfsmgr

  RUN_WITH_PARAMS
    "--lib" "${CMAKE_BINARY_DIR}/out/msxfs.dll"
)
