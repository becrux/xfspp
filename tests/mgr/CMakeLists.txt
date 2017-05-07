add_executable(tests_mgr_startup
  EXCLUDE_FROM_ALL
  startup.cpp
  ../../win32/library.cpp
  ../../win32/synch.cpp
  ../../win32/registry.cpp
  ../../win32/environment.cpp
  ../../log/log.cpp
  ../../common/version.cpp
  ../../util/string.cpp
)

target_link_libraries(tests_mgr_startup shlwapi)

add_dependencies(tests_mgr_startup xfsmgr)

add_test(NAME tests_mgr_startup COMMAND tests_mgr_startup ${CMAKE_BINARY_DIR}/out/msxfs.dll)
