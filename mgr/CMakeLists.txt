set(SOURCES
  ../win32/registry.cpp
  ../win32/thread.cpp
  ../win32/synch.cpp
  ../win32/msgwnd.cpp
  ../win32/uuid.cpp
  ../win32/error.cpp
  ../win32/library.cpp
  ../win32/shmem.cpp
  ../log/log.cpp
  ../common/version.cpp
  main.cpp
  mgr.def
)

file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/*.h*")

add_library(xfsmgr SHARED ${SOURCES} ${HEADERS})
set_target_properties(xfsmgr PROPERTIES OUTPUT_NAME "msxfs")

target_link_libraries(xfsmgr rpcrt4 shlwapi)

add_custom_command(TARGET xfsmgr
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:xfsmgr>
	${OUTPUT_DIRECTORY})
