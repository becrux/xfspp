set(SOURCES
  src/buffer.c
  src/hook.c
  src/trampoline.c
  src/hde/hde32.c
  src/hde/hde64.c
)

include_directories(src include)

add_library(minhook ${SOURCES})

add_custom_command(TARGET minhook
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:minhook>
    ${CMAKE_BINARY_DIR})
