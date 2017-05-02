cmake_minimum_required(VERSION 3.0.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(xfspp)

add_definitions(
  -DNOMINMAX
  -D_UNICODE
  -DUNICODE
  -DWINVER=0x0600
  -D_WIN32_WINNT=0x0600
  -DGTEST_HAS_PTHREAD=0
)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/cen/320)

if(MSVC)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  if(${CMAKE_GENERATOR_TOOLSET} EQUAL "v120_CTP_Nov2012")
    add_definitions(-DGTEST_HAS_TR1_TUPLE=0)
  endif()

  # /GF - String pooling
  # /MP - Parallel build
  set(CMAKE_CXX_FLAGS "/Wall /wd4710 /wd4820 /wd4668 /EHa /GR /fp:fast /DWIN32 /D_WINDOWS")
  
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
  
  if(${CMAKE_GENERATOR_TOOLSET} MATCHES "^LLVM.*")
    set(CLANG_FLAGS "-Xclang -std=c++11 -std=gnu++11 -Wall -Wextra -Wuninitialized -Wold-style-cast -Woverloaded-virtual -Wnoexcept -Wnon-virtual-dtor -Winit-self -Wmissing-include-dirs -Wunused-parameter -Wctor-dtor-privacy -Wswitch-default -Wshadow -Wno-unknown-pragmas -Wundef -Wredundant-decls")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CLANG_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CLANG_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${CLANG_FLAGS}")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${CLANG_FLAGS}")
  endif()
else()
  set(CMAKE_CXX_FLAGS "-frtti -fexceptions -std=c++11 -std=gnu++11 -pedantic -Wall -Wextra -Wuninitialized -Wold-style-cast -Woverloaded-virtual -Wnoexcept -Wnon-virtual-dtor -Winit-self -Wmissing-include-dirs -Wunused-parameter -Wctor-dtor-privacy -Wswitch-default -Wshadow -Wno-unknown-pragmas -Wundef -Wredundant-decls")
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -g3 ${CMAKE_CXX_FLAGS}")
  set(CMAKE_CXX_FLAGS_RELEASE "-s -O3 ${CMAKE_CXX_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--subsystem,windows,--kill-at,--enable-stdcall-fixup ${CMAKE_SHARED_LINKER_FLAGS}")
endif()

get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
  if ((NOT (_variableName MATCHES "^CMAKE_CXX_COMPILER_ID_PLATFORM_CONTENT$")) AND
      (NOT (_variableName MATCHES "^CMAKE_CXX_COMPILER_PRODUCED_FILES$")) AND
	  (NOT (_variableName MATCHES "^CMAKE_CXX_COMPILER_PRODUCED_OUTPUT$")) AND
	  (NOT (_variableName MATCHES "^CMAKE_CXX_COMPILER_ID_TOOL_MATCH_INDEX$")) AND
	  (NOT (_variableName MATCHES "^CMAKE_CXX_COMPILER_ID_TOOL_MATCH_REGEX$")) AND
	  (NOT (_variableName MATCHES "^CMAKE_C_COMPILER_ID_PLATFORM_CONTENT$")) AND
      (NOT (_variableName MATCHES "^CMAKE_C_COMPILER_PRODUCED_FILES$")) AND
	  (NOT (_variableName MATCHES "^CMAKE_C_COMPILER_PRODUCED_OUTPUT$")) AND
	  (NOT (_variableName MATCHES "^CMAKE_C_COMPILER_ID_TOOL_MATCH_INDEX$")) AND
	  (NOT (_variableName MATCHES "^CMAKE_C_COMPILER_ID_TOOL_MATCH_REGEX$")))
    message(STATUS "${_variableName}=${${_variableName}}")
  endif()
endforeach()

message(STATUS "Environment variables:")
execute_process(COMMAND "${CMAKE_COMMAND}" "-E" "environment")

execute_process(COMMAND ${CMAKE_COMMAND} "-E" "make_directory" "${CMAKE_SOURCE_DIR}/ext" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

if((NOT EXISTS ${CMAKE_SOURCE_DIR}/ext/googletest) AND (NOT (${CMAKE_GENERATOR_TOOLSET} MATCHES "^LLVM.*")))
  message(STATUS "Downloading latest GoogleTest release ...")
  file(DOWNLOAD https://github.com/google/googletest/archive/release-1.8.0.zip ${CMAKE_BINARY_DIR}/gtest.zip)
  execute_process(COMMAND ${CMAKE_COMMAND} "-E" "tar" "xvf" "${CMAKE_BINARY_DIR}/gtest.zip" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ext)
  execute_process(COMMAND ${CMAKE_COMMAND} "-E" "rename" "googletest-release-1.8.0" "googletest" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ext)
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/ext/sqlite)
  message(STATUS "Downloading latest SQLite release ...")
  file(DOWNLOAD https://www.sqlite.org/2017/sqlite-amalgamation-3180000.zip ${CMAKE_BINARY_DIR}/sqlite.zip)
  execute_process(COMMAND ${CMAKE_COMMAND} "-E" "tar" "xvf" "${CMAKE_BINARY_DIR}/sqlite.zip" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ext)
  execute_process(COMMAND ${CMAKE_COMMAND} "-E" "rename" "sqlite-amalgamation-3180000" "sqlite" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ext)
endif()

if(NOT (${CMAKE_GENERATOR_TOOLSET} MATCHES "^LLVM.*"))
  add_subdirectory(${CMAKE_SOURCE_DIR}/ext/googletest)

  enable_testing()
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif()

add_subdirectory(mgr)
add_subdirectory(sp)

if(NOT (${CMAKE_GENERATOR_TOOLSET} MATCHES "^LLVM.*"))
  add_subdirectory(tests)
endif()
