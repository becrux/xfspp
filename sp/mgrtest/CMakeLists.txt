set(SOURCES
  ../../win32/thread.cpp
  ../../win32/synch.cpp
  ../../win32/thread.cpp
  ../../win32/timer.cpp
  ../../win32/registry.cpp
  ../../win32/environment.cpp
  ../../win32/exception.cpp
  ../../win32/library.cpp
  ../../xfs/registry.cpp
  ../../xfs/allocator.cpp
  ../../xfs/exception.cpp
  ../../xfs/version.cpp
  ../../log/log.cpp
  ../../util/string.cpp
  main.cpp
  mgrtest.def
)

file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/*.h*")

add_library(mgrtest SHARED ${SOURCES} ${HEADERS})

add_dependencies(mgrtest fmt)

target_link_libraries(mgrtest shlwapi fmt)

add_custom_command(TARGET mgrtest
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:mgrtest>
    ${OUTPUT_DIRECTORY})
