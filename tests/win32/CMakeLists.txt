link_directories(${CMAKE_BINARY_DIR})

ADD_XFSPP_TEST(tests_win32_handle
  SOURCES
    handle.cpp
    ../../win32/filesystem.cpp
    ../../win32/exception.cpp
    ../../util/string.cpp

  DEPS
    minhook

  LIBS
    shlwapi
    minhook
)

ADD_XFSPP_TEST(tests_win32_string
  SOURCES
    string.cpp
    ../../win32/exception.cpp
    ../../util/string.cpp

  DEPS
    minhook

  LIBS
    shlwapi
    minhook
)

ADD_XFSPP_TEST(tests_win32_synch
  SOURCES
    synch.cpp
    ../../win32/synch.cpp
    ../../win32/thread.cpp
    ../../win32/environment.cpp
    ../../win32/registry.cpp
    ../../win32/exception.cpp
    ../../log/log.cpp
    ../../util/string.cpp

  DEPS
    minhook

  LIBS
    shlwapi
    minhook
)

ADD_XFSPP_TEST(tests_win32_thread
  SOURCES
    thread.cpp
    ../../win32/thread.cpp
    ../../win32/environment.cpp
    ../../win32/registry.cpp
    ../../win32/exception.cpp
    ../../log/log.cpp
    ../../util/string.cpp

  DEPS
    minhook

  LIBS
    shlwapi
    minhook
)

ADD_XFSPP_TEST(tests_win32_timer
  SOURCES
    timer.cpp
    ../../win32/timer.cpp
    ../../win32/thread.cpp
    ../../win32/synch.cpp
    ../../win32/environment.cpp
    ../../win32/registry.cpp
    ../../win32/exception.cpp
    ../../log/log.cpp
    ../../util/string.cpp

  DEPS
    minhook

  LIBS
    shlwapi
    minhook
)

ADD_XFSPP_TEST(tests_win32_uuid
  SOURCES
    uuid.cpp
    ../../win32/uuid.cpp
    ../../win32/exception.cpp
    ../../util/string.cpp

  DEPS
    minhook

  LIBS
    shlwapi
    rpcrt4
    minhook
)

ADD_XFSPP_TEST(tests_win32_library
  SOURCES
    library.cpp
    ../../win32/library.cpp
    ../../win32/environment.cpp
    ../../win32/registry.cpp
    ../../win32/exception.cpp
    ../../log/log.cpp
    ../../util/string.cpp

  DEPS
    minhook

  LIBS
    shlwapi
    minhook
)

ADD_XFSPP_TEST(tests_win32_shared_memory
  SOURCES
    shmem.cpp
    ../../win32/shmem.cpp
    ../../win32/synch.cpp
    ../../win32/uuid.cpp
    ../../win32/environment.cpp
    ../../win32/registry.cpp
    ../../win32/exception.cpp
    ../../log/log.cpp
    ../../util/string.cpp

  DEPS
    minhook

  LIBS
    rpcrt4
    shlwapi
    minhook
)

ADD_XFSPP_TEST(tests_win32_registry
  SOURCES
    registry.cpp
    ../../win32/registry.cpp
    ../../win32/environment.cpp
    ../../win32/exception.cpp
    ../../log/log.cpp
    ../../util/string.cpp

  DEPS
    minhook

  LIBS
    shlwapi
    minhook
)

ADD_XFSPP_TEST(tests_win32_environment
  SOURCES
    environment.cpp
    ../../win32/environment.cpp
    ../../win32/exception.cpp
    ../../util/string.cpp

  DEPS
    minhook

  LIBS
    shlwapi
    minhook
)

ADD_XFSPP_TEST(tests_win32_window
  SOURCES
    msgwnd.cpp
    ../../win32/msgwnd.cpp
    ../../win32/synch.cpp
    ../../win32/uuid.cpp
    ../../win32/thread.cpp
    ../../win32/environment.cpp
    ../../win32/registry.cpp
    ../../win32/exception.cpp
    ../../log/log.cpp
    ../../util/string.cpp

  DEPS
    minhook

  LIBS
    rpcrt4
    shlwapi
    minhook
)
