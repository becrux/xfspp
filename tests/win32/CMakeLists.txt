add_definitions(-DTEST_LOG)

add_executable(tests_win32_handle
  handle.cpp
  ../../win32/error.cpp
)

add_test(NAME tests_win32_handle COMMAND tests_win32_handle)

add_executable(tests_win32_synch
  synch.cpp
  ../../win32/synch.cpp
  ../../win32/error.cpp
)

add_test(NAME tests_win32_synch COMMAND tests_win32_synch)

add_executable(tests_win32_thread
  thread.cpp
  ../../win32/thread.cpp
  ../../win32/error.cpp
  ../../log/log.cpp
)

add_test(NAME tests_win32_thread COMMAND tests_win32_thread)

add_executable(tests_win32_timer
  timer.cpp
  ../../win32/timer.cpp
  ../../win32/thread.cpp
  ../../win32/synch.cpp
  ../../win32/error.cpp
  ../../log/log.cpp
)

add_test(NAME tests_win32_timer COMMAND tests_win32_timer)

add_executable(tests_win32_uuid
  uuid.cpp
  ../../win32/uuid.cpp
  ../../win32/error.cpp
)

target_link_libraries(tests_win32_uuid rpcrt4)

add_test(NAME tests_win32_uuid COMMAND tests_win32_uuid)

add_executable(tests_win32_library
  library.cpp
  ../../win32/library.cpp
  ../../win32/error.cpp
  ../../log/log.cpp
)

add_test(NAME tests_win32_library COMMAND tests_win32_library)

add_executable(tests_win32_shared_memory
  shmem.cpp
  ../../win32/shmem.cpp
  ../../win32/error.cpp
  ../../win32/synch.cpp
  ../../win32/uuid.cpp
  ../../log/log.cpp
)

target_link_libraries(tests_win32_shared_memory rpcrt4)

add_test(NAME tests_win32_shared_memory COMMAND tests_win32_shared_memory)

add_executable(tests_win32_registry
  registry.cpp
  ../../win32/registry.cpp
  ../../win32/error.cpp
  ../../log/log.cpp
  ../../util/string.cpp
)

add_test(NAME tests_win32_registry COMMAND tests_win32_registry)

add_executable(tests_win32_window
  msgwnd.cpp
  ../../win32/msgwnd.cpp
  ../../win32/error.cpp
  ../../win32/synch.cpp
  ../../win32/uuid.cpp
  ../../win32/thread.cpp
  ../../log/log.cpp
)

target_link_libraries(tests_win32_window rpcrt4)

add_test(NAME tests_win32_window COMMAND tests_win32_window)
