add_executable(tests_win32_handle
  EXCLUDE_FROM_ALL
  handle.cpp
)

add_test(NAME tests_win32_handle COMMAND tests_win32_handle)

add_executable(tests_win32_synch
  EXCLUDE_FROM_ALL
  synch.cpp
  ../../win32/synch.cpp
)

add_test(NAME tests_win32_synch COMMAND tests_win32_synch)

add_executable(tests_win32_thread
  EXCLUDE_FROM_ALL
  thread.cpp
  ../../win32/thread.cpp
  ../../win32/environment.cpp
  ../../win32/registry.cpp
  ../../log/log.cpp
  ../../util/string.cpp
)

target_link_libraries(tests_win32_thread shlwapi)

add_test(NAME tests_win32_thread COMMAND tests_win32_thread)

add_executable(tests_win32_timer
  EXCLUDE_FROM_ALL
  timer.cpp
  ../../win32/timer.cpp
  ../../win32/thread.cpp
  ../../win32/synch.cpp
  ../../win32/environment.cpp
  ../../win32/registry.cpp
  ../../log/log.cpp
  ../../util/string.cpp
)

target_link_libraries(tests_win32_timer shlwapi)

add_test(NAME tests_win32_timer COMMAND tests_win32_timer)

add_executable(tests_win32_uuid
  EXCLUDE_FROM_ALL
  uuid.cpp
  ../../win32/uuid.cpp
)

target_link_libraries(tests_win32_uuid rpcrt4)

add_test(NAME tests_win32_uuid COMMAND tests_win32_uuid)

add_executable(tests_win32_library
  EXCLUDE_FROM_ALL
  library.cpp
  ../../win32/library.cpp
  ../../win32/environment.cpp
  ../../win32/registry.cpp
  ../../log/log.cpp
  ../../util/string.cpp
)

target_link_libraries(tests_win32_library shlwapi)

add_test(NAME tests_win32_library COMMAND tests_win32_library)

add_executable(tests_win32_shared_memory
  EXCLUDE_FROM_ALL
  shmem.cpp
  ../../win32/shmem.cpp
  ../../win32/synch.cpp
  ../../win32/uuid.cpp
  ../../win32/environment.cpp
  ../../win32/registry.cpp
  ../../log/log.cpp
  ../../util/string.cpp
)

target_link_libraries(tests_win32_shared_memory rpcrt4 shlwapi)

add_test(NAME tests_win32_shared_memory COMMAND tests_win32_shared_memory)

add_executable(tests_win32_registry
  EXCLUDE_FROM_ALL
  registry.cpp
  ../../win32/registry.cpp
  ../../win32/environment.cpp
  ../../log/log.cpp
  ../../util/string.cpp
)

target_link_libraries(tests_win32_registry shlwapi)

add_test(NAME tests_win32_registry COMMAND tests_win32_registry)

add_executable(tests_win32_window
  EXCLUDE_FROM_ALL
  msgwnd.cpp
  ../../win32/msgwnd.cpp
  ../../win32/synch.cpp
  ../../win32/uuid.cpp
  ../../win32/thread.cpp
  ../../win32/environment.cpp
  ../../win32/registry.cpp
  ../../log/log.cpp
  ../../util/string.cpp
)

target_link_libraries(tests_win32_window rpcrt4 shlwapi)

add_test(NAME tests_win32_window COMMAND tests_win32_window)
