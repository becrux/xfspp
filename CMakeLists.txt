cmake_minimum_required(VERSION 3.0.0)
project(xfspp)

add_definitions(-DNOMINMAX -D_UNICODE -DUNICODE)

include_directories(${CMAKE_SOURCE_DIR})

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
