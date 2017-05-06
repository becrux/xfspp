add_executable(startupTests
  startup.cpp
  ../../win32/library.cpp
  ../../win32/synch.cpp
  ../../win32/error.cpp
  ../../win32/registry.cpp
  ../../log/log.cpp
  ../../common/version.cpp
)

add_dependencies(startupTests xfsmgr)

add_test(NAME startup_tests COMMAND startupTests ${CMAKE_BINARY_DIR}/out/msxfs.dll)
