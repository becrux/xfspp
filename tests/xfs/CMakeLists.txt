ADD_XFSPP_TEST(tests_xfs_version
  SOURCES
    version.cpp
    ../../xfs/version.cpp
)

# ADD_XFSPP_TEST(tests_xfs_manager
#   SOURCES
#     xfs_manager.cpp
#     ../../win32/exception.cpp
#     ../../win32/msgwnd.cpp
#     ../../win32/uuid.cpp
#     ../../win32/registry.cpp
#     ../../win32/synch.cpp
#     ../../win32/thread.cpp
#     ../../win32/environment.cpp
#     ../../log/log.cpp
#     ../../util/string.cpp
# 
#   LIBS
#     rpcrt4
#     shlwapi
#     minhook
# 
#   DEPS
#     mgrtest
#     xfsmgr    
# 
#   RUN_WITH_PARAMS
#     "--lib" "${CMAKE_BINARY_DIR}/out/msxfs.dll"
# )
