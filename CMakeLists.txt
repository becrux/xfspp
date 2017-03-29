cmake_minimum_required(VERSION 3.0.0)
project(xfspp)

add_definitions(-DNOMINMAX)

include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
  main.cpp
  win32/handle.cpp
  win32/synch.cpp
  win32/thread.cpp
  win32/timer.cpp
  sp/dispatcher.cpp
  sp/task.cpp
  main.cpp
)

add_executable(test_main ${SOURCES})  
