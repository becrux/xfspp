cmake_minimum_required(VERSION 3.0.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(xfspp C CXX)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

execute_process(COMMAND ${CMAKE_COMMAND} "-E" "make_directory" "${CMAKE_SOURCE_DIR}/ext")

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/ext/sqlite)
  message(STATUS "Downloading latest SQLite release ...")
  file(DOWNLOAD http://sqlite.org/2017/sqlite-amalgamation-3190200.zip ${CMAKE_BINARY_DIR}/sqlite.zip)
  execute_process(COMMAND ${CMAKE_COMMAND} "-E" "tar" "xvf" "${CMAKE_BINARY_DIR}/sqlite.zip" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ext)
  execute_process(COMMAND ${CMAKE_COMMAND} "-E" "rename" "sqlite-amalgamation-3190200" "sqlite" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ext)
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/ext/catch)
  message(STATUS "Downloading latest Catch release ...")
  file(DOWNLOAD https://github.com/philsquared/Catch/releases/download/v1.9.6/catch.hpp ${CMAKE_SOURCE_DIR}/ext/catch/catch.hpp)
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/ext/fmt)
  message(STATUS "Downloading latest fmt release ...")
  execute_process(COMMAND ${CMAKE_COMMAND} "-E" "make_directory" "${CMAKE_BINARY_DIR}/temp")
  file(DOWNLOAD https://github.com/fmtlib/fmt/archive/4.0.0.zip ${CMAKE_BINARY_DIR}/fmt.zip)
  execute_process(COMMAND ${CMAKE_COMMAND} "-E" "tar" "xvf" "${CMAKE_BINARY_DIR}/fmt.zip" WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/temp)
  execute_process(COMMAND ${CMAKE_COMMAND} "-E" "make_directory" "${CMAKE_SOURCE_DIR}/ext/fmt")
  execute_process(COMMAND ${CMAKE_COMMAND} "-E" "copy_directory" "${CMAKE_BINARY_DIR}/temp/fmt-4.0.0/fmt" ${CMAKE_SOURCE_DIR}/ext/fmt)
  execute_process(COMMAND ${CMAKE_COMMAND} "-E" "remove" "-f" "${CMAKE_SOURCE_DIR}/ext/fmt/CMakeLists.txt")
endif()

include(CTest)
enable_testing()

add_definitions(
  -DNOMINMAX
  -D_UNICODE
  -DUNICODE
  -DWINVER=0x0600
  -D_WIN32_WINNT=0x0600
  -DWIN32
  -D_WINDOWS
  -D_CRT_SECURE_NO_WARNINGS
)

include_directories(${CMAKE_SOURCE_DIR} SYSTEM ${CMAKE_SOURCE_DIR}/cen/320 ${CMAKE_SOURCE_DIR}/ext)

add_library(fmt
  STATIC
  "${CMAKE_SOURCE_DIR}/ext/fmt/format.cc"
  "${CMAKE_SOURCE_DIR}/ext/fmt/ostream.cc"
  "${CMAKE_SOURCE_DIR}/ext/fmt/posix.cc"
  "${CMAKE_SOURCE_DIR}/ext/fmt/printf.cc"
)

if(MSVC)
  target_compile_options(fmt PRIVATE "/TP")
endif()

if(MSVC)
  set(CMAKE_CXX_FLAGS "/Wall /wd4710 /wd4820 /wd4668 /wd4514 /wd4355 /wd4350 /wd4640 /wd4711 /EHa /GR /fp:fast")

  if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument")
  endif()
  
  set(CMAKE_CXX_FLAGS_DEBUG "/Ob0 /D_DEBUG /MDd /Zi /Od /RTC1 ${CMAKE_CXX_FLAGS}")
  
  set(CMAKE_CXX_FLAGS_RELEASE "/Oy /GL /Gy /MD /O2 /Ob2 /DNDEBUG ${CMAKE_CXX_FLAGS}")
  
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Oy- /GL /Gy /MD /Zi /O2 /Ob1 /DNDEBUG ${CMAKE_CXX_FLAGS}")
  
  set(CMAKE_CXX_FLAGS_MINSIZEREL "/Oy /GL /Gy /MD /O1 /Ob1 /DNDEBUG ${CMAKE_CXX_FLAGS}")

  set(LINKER_FLAGS "/DYNAMICBASE /NXCOMPAT /LARGEADDRESSAWARE /NOLOGO")
  set(EXE_LINKER_FLAGS "/SUBSYSTEM:CONSOLE /ENTRY:wmainCRTStartup")
  set(CMAKE_EXE_LINKER_FLAGS "${EXE_LINKER_FLAGS} ${LINKER_FLAGS}")
  
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/DEBUG ${CMAKE_EXE_LINKER_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/RELEASE /OPT:REF /LTCG /OPT:ICF /INCREMENTAL:NO ${CMAKE_EXE_LINKER_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/DEBUG /RELEASE /LTCG /OPT:REF /OPT:ICF /INCREMENTAL:NO /DEBUGTYPE:cv,fixup ${CMAKE_EXE_LINKER_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "/RELEASE /LTCG /OPT:REF /OPT:ICF /INCREMENTAL:NO ${CMAKE_EXE_LINKER_FLAGS}")

  set(CMAKE_SHARED_LINKER_FLAGS "${LINKER_FLAGS} /NOASSEMBLY /DLL")
  set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/DEBUG ${CMAKE_SHARED_LINKER_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/RELEASE /OPT:REF /LTCG /OPT:ICF /INCREMENTAL:NO ${CMAKE_SHARED_LINKER_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "/DEBUG /RELEASE /LTCG /OPT:REF /OPT:ICF /INCREMENTAL:NO /DEBUGTYPE:cv,fixup ${CMAKE_SHARED_LINKER_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "/RELEASE /LTCG /OPT:REF /OPT:ICF /INCREMENTAL:NO ${CMAKE_SHARED_LINKER_FLAGS}")
else()
  set(CMAKE_CXX_FLAGS "-municode -frtti -fexceptions -std=c++11 -std=gnu++11 -pedantic -Wall -Wextra -Wuninitialized -Wold-style-cast -Woverloaded-virtual -Wnoexcept -Wnon-virtual-dtor -Winit-self -Wmissing-include-dirs -Wunused-parameter -Wctor-dtor-privacy -Wswitch-default -Wshadow -Wno-unknown-pragmas -Wundef -Wredundant-decls")
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -g3 -ggdb -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-inline -fno-elide-constructors ${CMAKE_CXX_FLAGS}")
  set(CMAKE_CXX_FLAGS_RELEASE "-s -O3 ${CMAKE_CXX_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--subsystem,windows,--kill-at,--enable-stdcall-fixup ${CMAKE_SHARED_LINKER_FLAGS}")
  
  string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)
  if(CMAKE_BUILD_TYPE_LOWER STREQUAL "debug")
    set(CMAKE_CXX_FLAGS_DEBUG "--coverage ${CMAKE_CXX_FLAGS_DEBUG}")
    set(CMAKE_EXE_LINKER_FLAGS "--coverage ${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS "--coverage ${CMAKE_SHARED_LINKER_FLAGS}")

    find_program(GCOV_PATH gcov)
    if(NOT GCOV_PATH)
      message(FATAL_ERROR "gcov not found!")
    endif()
  endif()
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

set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
file(MAKE_DIRECTORY ${OUTPUT_DIRECTORY})

add_custom_target(tests
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/tests_xml)

function(ADD_XFSPP_TEST targetName)
  set(sources SOURCES)
  set(args ARGS)
  set(libs LIBS)
  set(deps DEPENDS)
  cmake_parse_arguments(PARSED_ARGS "" "" "SOURCES;DEPS;LIBS;TIMEOUT;RUN_WITH_PARAMS" ${ARGN})

  add_executable(${targetName}
    EXCLUDE_FROM_ALL
    ${PARSED_ARGS_SOURCES})

  if(PARSED_ARGS_LIBS)
    target_link_libraries(${targetName} ${PARSED_ARGS_LIBS})
  endif()
  
  if(PARSED_ARGS_DEPS)
    add_dependencies(${targetName} ${PARSED_ARGS_DEPS})
  endif()

  add_dependencies(tests ${targetName})
  
  add_test(NAME ${targetName} COMMAND ${targetName} ${PARSED_ARGS_RUN_WITH_PARAMS} "-s" "-d" "yes" "-r" "junit" "-o" "${CMAKE_BINARY_DIR}/tests_xml/${targetName}.xml")

  if(PARSED_ARGS_TIMEOUT)
    set_tests_properties(${targetName} PROPERTIES TIMEOUT ${PARSED_ARGS_TIMEOUT})
  else()
    set_tests_properties(${targetName} PROPERTIES TIMEOUT 120)
  endif()
endfunction()

add_subdirectory(mgr)
add_subdirectory(sp)
add_subdirectory(tests)
