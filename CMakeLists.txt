cmake_minimum_required(VERSION 3.0.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(xfspp)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

execute_process(COMMAND ${CMAKE_COMMAND} "-E" "make_directory" "${CMAKE_SOURCE_DIR}/ext" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/ext/sqlite)
  message(STATUS "Downloading latest SQLite release ...")
  file(DOWNLOAD https://www.sqlite.org/2017/sqlite-amalgamation-3180000.zip ${CMAKE_BINARY_DIR}/sqlite.zip)
  execute_process(COMMAND ${CMAKE_COMMAND} "-E" "tar" "xvf" "${CMAKE_BINARY_DIR}/sqlite.zip" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ext)
  execute_process(COMMAND ${CMAKE_COMMAND} "-E" "rename" "sqlite-amalgamation-3180000" "sqlite" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ext)
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/ext/catch)
  message(STATUS "Downloading latest Catch release ...")
  file(DOWNLOAD https://github.com/philsquared/Catch/releases/download/v1.9.3/catch.hpp ${CMAKE_SOURCE_DIR}/ext/catch/catch.hpp)
endif()

enable_testing()

add_definitions(
  -DNOMINMAX
  -D_UNICODE
  -DUNICODE
  -DWINVER=0x0600
  -D_WIN32_WINNT=0x0600
  -DWIN32
  -D_WINDOWS
)

include_directories(${CMAKE_SOURCE_DIR} SYSTEM ${CMAKE_SOURCE_DIR}/cen/320 ${CMAKE_SOURCE_DIR}/ext)

if(MSVC)
  set(CMAKE_CXX_FLAGS "/Wall /wd4710 /wd4820 /wd4668 /wd4514 /wd4355 /wd4350 /wd4640 /EHa /GR /fp:fast")
  
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

set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
file(MAKE_DIRECTORY ${OUTPUT_DIRECTORY})

add_custom_target(tests
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/tests_xml)

function(ADD_XFSPP_TEST targetName)
  set(sources SOURCES)
  set(args ARGS)
  set(libs LIBS)
  set(deps DEPENDS)
  cmake_parse_arguments(PARSED_ARGS "" "" "SOURCES;DEPS;LIBS;RUN_WITH_PARAMS" ${ARGN})
  
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
endfunction()

add_subdirectory(mgr)
add_subdirectory(sp)
add_subdirectory(tests)
