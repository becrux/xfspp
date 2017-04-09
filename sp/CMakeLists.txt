cmake_minimum_required(VERSION 3.0.0)

set(SOURCES
  ../win32/thread.cpp
  ../win32/synch.cpp
  ../win32/thread.cpp
  ../win32/timer.cpp
  ../win32/error.cpp
  ../log/log.cpp
  dispatcher.cpp
  task.cpp
  main.cpp
  sp.def
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
  file(GLOB CEN_HEADER_FILES RELATIVE ${CMAKE_SOURCE_DIR} "cen/320/*.h")
  list(APPEND HEADERS ${CEN_HEADER_FILES})
endforeach()

add_library(test_sp SHARED ${SOURCES} ${HEADERS})
