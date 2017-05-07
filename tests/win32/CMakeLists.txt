ADD_XFSPP_TEST(tests_win32_handle
  SOURCES
    handle.cpp
)

ADD_XFSPP_TEST(tests_win32_synch
  SOURCES
    synch.cpp
    ../../win32/synch.cpp
)

ADD_XFSPP_TEST(tests_win32_thread
  SOURCES
    thread.cpp
    ../../win32/thread.cpp
    ../../win32/environment.cpp
    ../../win32/registry.cpp
    ../../log/log.cpp
    ../../util/string.cpp

  LIBS
    shlwapi
)

ADD_XFSPP_TEST(tests_win32_timer
  SOURCES
    timer.cpp
    ../../win32/timer.cpp
    ../../win32/thread.cpp
    ../../win32/synch.cpp
    ../../win32/environment.cpp
    ../../win32/registry.cpp
    ../../log/log.cpp
    ../../util/string.cpp
  
  LIBS
    shlwapi
)

ADD_XFSPP_TEST(tests_win32_uuid
  SOURCES
    uuid.cpp
    ../../win32/uuid.cpp

  LIBS
    rpcrt4
)

ADD_XFSPP_TEST(tests_win32_library
  SOURCES
    library.cpp
    ../../win32/library.cpp
    ../../win32/environment.cpp
    ../../win32/registry.cpp
    ../../log/log.cpp
    ../../util/string.cpp
  
  LIBS
    shlwapi
)

ADD_XFSPP_TEST(tests_win32_shared_memory
  SOURCES
    shmem.cpp
    ../../win32/shmem.cpp
    ../../win32/synch.cpp
    ../../win32/uuid.cpp
    ../../win32/environment.cpp
    ../../win32/registry.cpp
    ../../log/log.cpp
    ../../util/string.cpp
  
  LIBS
    rpcrt4
    shlwapi
)

ADD_XFSPP_TEST(tests_win32_registry
  SOURCES
    registry.cpp
    ../../win32/registry.cpp
    ../../win32/environment.cpp
    ../../log/log.cpp
    ../../util/string.cpp
    
  LIBS
    shlwapi
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
    ../../log/log.cpp
    ../../util/string.cpp
    
  LIBS
    rpcrt4
    shlwapi
)
