add_executable(startupTests
  startup.cpp
  ../../win32/library.cpp
  ../../win32/synch.cpp
  ../../win32/error.cpp
  ../../win32/registry.cpp
  ../../log/log.cpp
)

target_link_libraries(startupTests gtest gtest_main)

add_test(NAME startupTests COMMAND startupTests)
