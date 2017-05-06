add_definitions(-DTEST_LOG)

add_executable(tests_mgr_startup
  startup.cpp
  ../../win32/library.cpp
  ../../win32/synch.cpp
  ../../win32/error.cpp
  ../../win32/registry.cpp
  ../../log/log.cpp
  ../../common/version.cpp
  ../../util/string.cpp
)

add_dependencies(tests_mgr_startup xfsmgr)

add_test(NAME tests_mgr_startup COMMAND tests_mgr_startup ${CMAKE_BINARY_DIR}/out/msxfs.dll)
