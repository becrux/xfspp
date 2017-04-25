cmake_minimum_required(VERSION 3.0.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(xfspp)

add_definitions(
  -DNOMINMAX
  -D_UNICODE
  -DUNICODE
  -DWINVER=0x0600
  -D_WIN32_WINNT=0x0600
)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/cen/320)

if(MSVC)
  # /GF - String pooling
  # /MP - Parallel build
  set(CMAKE_CXX_FLAGS "/W4 /EHa /GR /DWIN32 /D_WINDOWS /GR")
  
  # /Zi - Create debugging information
  # /Od - Disable optimization
  # /D_DEBUG - #define _DEBUG
  # /MTd - Statically link the multithreaded debug version of the CRT
  # /MDd - Dynamically link the multithreaded debug version of the CRT
  # /RTC1 - Run time checks
  set(CMAKE_CXX_FLAGS_DEBUG "/Ob0 /D_DEBUG ${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS}")
  
  # /DNDEBUG - Disables asserts
  # /MT - Statically link the multithreaded release version of the CRT
  # /MD - Dynamically link the multithreaded release version of the CRT
  # /O2 - Optimize for speed
  # /Oy - Enable frame pointer omission (FPO) (otherwise CMake will automatically turn it off)
  # /GL - Link time code generation (whole program optimization)
  # /Gy - Function-level linking
  set(CMAKE_CXX_FLAGS_RELEASE "/Oy /GL /Gy /MT ${CMAKE_CXX_FLAGS_RELEASE} ${CMAKE_CXX_FLAGS}")
  
  # /Oy- - Disable frame pointer omission (FPO)
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Oy- /GL /Gy ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${CMAKE_CXX_FLAGS}")
  
  # /O1 - Optimize for size
  set(CMAKE_CXX_FLAGS_MINSIZEREL "/Oy /GL /Gy ${CMAKE_CXX_FLAGS_MINSIZEREL} ${CMAKE_CXX_FLAGS}")
  
  # /DYNAMICBASE - Address space load randomization (ASLR)
  # /NXCOMPAT - Data execution prevention (DEP)
  # /LARGEADDRESSAWARE - >2GB user address space on x86
  # /VERSION - Embed version information in PE header
  set(CMAKE_EXE_LINKER_FLAGS "/DYNAMICBASE /NXCOMPAT /LARGEADDRESSAWARE")
  
  # /DEBUG - Create a PDB
  # /LTCG - Link time code generation (whole program optimization)
  # /OPT:REF /OPT:ICF - Fold out duplicate code at link step
  # /INCREMENTAL:NO - Required to use /LTCG
  # /DEBUGTYPE:cv,fixup - Additional data embedded in the PDB (requires /INCREMENTAL:NO, so not on for Debug)
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/DEBUG")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/RELEASE /OPT:REF /LTCG /OPT:ICF /INCREMENTAL:NO")
  set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/DEBUG /RELEASE /LTCG /OPT:REF /OPT:ICF /INCREMENTAL:NO /DEBUGTYPE:cv,fixup")
  set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "/RELEASE /LTCG /OPT:REF /OPT:ICF /INCREMENTAL:NO")
else()
  set(CMAKE_CXX_FLAGS "-frtti -fexceptions -std=c++11 -std=gnu++11 -pedantic -Wall -Wextra -Wuninitialized -Wold-style-cast -Woverloaded-virtual -Wnoexcept -Wnon-virtual-dtor -Winit-self -Wmissing-include-dirs -Wunused-parameter -Wctor-dtor-privacy -Wswitch-default -Wshadow -Wno-unknown-pragmas -Wundef -Wredundant-decls")
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -g3 ${CMAKE_CXX_FLAGS}")
  set(CMAKE_CXX_FLAGS_RELEASE "-s -O3 ${CMAKE_CXX_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--subsystem,windows,--kill-at,--enable-stdcall-fixup ${CMAKE_SHARED_LINKER_FLAGS}")
endif()

message(STATUS "CMAKE_BINARY_DIR:         " ${CMAKE_BINARY_DIR})
message(STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "CMAKE_SOURCE_DIR:         " ${CMAKE_SOURCE_DIR})
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})
message(STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
message(STATUS "EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH})
message(STATUS "LIBRARY_OUTPUT_PATH:     " ${LIBRARY_OUTPUT_PATH})
message(STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})
message(STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND})
message(STATUS "CMAKE_ROOT: " ${CMAKE_ROOT})
message(STATUS "CMAKE_CURRENT_LIST_FILE: " ${CMAKE_CURRENT_LIST_FILE})
message(STATUS "CMAKE_CURRENT_LIST_LINE: " ${CMAKE_CURRENT_LIST_LINE})
message(STATUS "CMAKE_INCLUDE_PATH: " ${CMAKE_INCLUDE_PATH})
message(STATUS "CMAKE_LIBRARY_PATH: " ${CMAKE_LIBRARY_PATH})
message(STATUS "CMAKE_SYSTEM: " ${CMAKE_SYSTEM})
message(STATUS "CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME})
message(STATUS "CMAKE_SYSTEM_VERSION: " ${CMAKE_SYSTEM_VERSION})
message(STATUS "CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR})
message(STATUS "UNIX: " ${UNIX})
message(STATUS "WIN32: " ${WIN32})
message(STATUS "APPLE: " ${APPLE})
message(STATUS "MINGW: " ${MINGW})
message(STATUS "CYGWIN: " ${CYGWIN})
message(STATUS "BORLAND: " ${BORLAND})
message(STATUS "MSVC: " ${MSVC})
message(STATUS "MSVC_IDE: " ${MSVC_IDE})
message(STATUS "MSVC_VERSION: " ${MSVC_VERSION})
message(STATUS "MSVC60: " ${MSVC60})
message(STATUS "MSVC70: " ${MSVC70})
message(STATUS "MSVC71: " ${MSVC71})
message(STATUS "MSVC80: " ${MSVC80})
message(STATUS "MSVC90: " ${MSVC90})
message(STATUS "MSVC10: " ${MSVC10})
message(STATUS "MSVC11: " ${MSVC11})
message(STATUS "MSVC12: " ${MSVC12})
message(STATUS "CMAKE_COMPILER_2005: " ${CMAKE_COMPILER_2005})
message(STATUS "CMAKE_SKIP_RULE_DEPENDENCY: " ${CMAKE_SKIP_RULE_DEPENDENCY})
message(STATUS "CMAKE_SKIP_INSTALL_ALL_DEPENDENCY: " ${CMAKE_SKIP_INSTALL_ALL_DEPENDENCY})
message(STATUS "CMAKE_SKIP_RPATH: " ${CMAKE_SKIP_RPATH})
message(STATUS "CMAKE_VERBOSE_MAKEFILE: " ${CMAKE_VERBOSE_MAKEFILE})
message(STATUS "CMAKE_SUPPRESS_REGENERATION: " ${CMAKE_SUPPRESS_REGENERATION})
message(STATUS "CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS})
message(STATUS "CMAKE_C_FLAGS_DEBUG: " ${CMAKE_C_FLAGS_DEBUG})
message(STATUS "CMAKE_C_FLAGS_RELEASE: " ${CMAKE_C_FLAGS_RELEASE})
message(STATUS "CMAKE_C_FLAGS_RELWITHDEBINFO: " ${CMAKE_C_FLAGS_RELWITHDEBINFO})
message(STATUS "CMAKE_C_FLAGS_MINSIZEREL: " ${CMAKE_C_FLAGS_MINSIZEREL})
message(STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: " ${CMAKE_CXX_FLAGS_DEBUG})
message(STATUS "CMAKE_CXX_FLAGS_RELEASE: " ${CMAKE_CXX_FLAGS_RELEASE})
message(STATUS "CMAKE_CXX_FLAGS_RELWITHDEBINFO: " ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
message(STATUS "CMAKE_CXX_FLAGS_MINSIZEREL: " ${CMAKE_CXX_FLAGS_MINSIZEREL})
message(STATUS "CMAKE_EXE_LINKER_FLAGS: " ${CMAKE_EXE_LINKER_FLAGS})
message(STATUS "CMAKE_MODULE_LINKER_FLAGS: " ${CMAKE_MODULE_LINKER_FLAGS})
message(STATUS "CMAKE_STATIC_LINKER_FLAGS: " ${CMAKE_STATIC_LINKER_FLAGS})
message(STATUS "CMAKE_SHARED_LINKER_FLAGS: " ${CMAKE_SHARED_LINKER_FLAGS})
message(STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
message(STATUS "BUILD_SHARED_LIBS: " ${BUILD_SHARED_LIBS})
message(STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER})
message(STATUS "CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER})
message(STATUS "CMAKE_C_COMPILER_ID: " ${CMAKE_C_COMPILER_ID})
message(STATUS "CMAKE_CXX_COMPILER_ID: " ${CMAKE_CXX_COMPILER_ID})
message(STATUS "CMAKE_AR: " ${CMAKE_AR})
message(STATUS "CMAKE_RANLIB: " ${CMAKE_RANLIB})

add_subdirectory(mgr)
add_subdirectory(sp)
