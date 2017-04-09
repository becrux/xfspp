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

add_headers(HEADERS ${SOURCES})

add_library(test_sp SHARED ${SOURCES} ${HEADERS})
