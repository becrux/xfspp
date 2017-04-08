cmake_minimum_required(VERSION 3.0.0)
project(xfspp)

add_definitions(-DNOMINMAX -D_UNICODE -DUNICODE -DWINVER=0x0501 -D_WIN32_WINNT=0x0501)

include_directories(${CMAKE_SOURCE_DIR})

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

set(SOURCES
  main.cpp
  win32/handle.cpp
  win32/thread.cpp
  win32/synch.cpp
  win32/thread.cpp
  win32/timer.cpp
  win32/msgwnd.cpp
  win32/uuid.cpp
  sp/dispatcher.cpp
  sp/task.cpp
  log/log.cpp
  main.cpp
)

foreach(FILE ${SOURCES})
  get_filename_component(SOURCE_FILE_WE ${FILE} NAME_WE)
  get_filename_component(SOURCE_DIR ${FILE} DIRECTORY)
  set(HEADER_FILE_STR "${CMAKE_SOURCE_DIR}/${SOURCE_DIR}/${SOURCE_FILE_WE}.hpp")
  file(TO_CMAKE_PATH ${HEADER_FILE_STR} HEADER_FILE)
  if (EXISTS ${HEADER_FILE})
    list(APPEND HEADERS ${HEADER_FILE})
  endif()
  
  file(GLOB UTIL_HEADER_FILES RELATIVE ${CMAKE_SOURCE_DIR} "util/*.hpp")
  list(APPEND HEADERS ${UTIL_HEADER_FILES})
endforeach()

add_executable(test_main ${SOURCES} ${HEADERS})

target_link_libraries(test_main rpcrt4)
