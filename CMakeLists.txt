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

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/cen/320)

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

function(ADD_HEADERS HEADER_FILES_LIST)
  foreach(CPP_FILE ${ARGN})
    get_filename_component(ABS_FILE_PATH ${CPP_FILE} REALPATH)
    get_filename_component(SOURCE_FILE_WE ${ABS_FILE_PATH} NAME_WE)
    get_filename_component(SOURCE_DIR ${ABS_FILE_PATH} DIRECTORY)
    set(HEADER_FILE_STR "${SOURCE_DIR}/${SOURCE_FILE_WE}.hpp")
    file(TO_CMAKE_PATH ${HEADER_FILE_STR} HEADER_FILE)
    if (EXISTS ${HEADER_FILE})
      list(APPEND HEADER_FILES ${HEADER_FILE})
    endif()
  endforeach()

  file(GLOB UTIL_HEADER_FILES "${CMAKE_SOURCE_DIR}/util/*.hpp")
  list(APPEND HEADER_FILES ${UTIL_HEADER_FILES})
  file(GLOB CEN_HEADER_FILES "${CMAKE_SOURCE_DIR}/cen/320/*.h")
  list(APPEND HEADER_FILES ${CEN_HEADER_FILES})

  set(${HEADER_FILES_LIST} ${HEADER_FILES} PARENT_SCOPE)
endfunction()

add_subdirectory(mgr)
add_subdirectory(sp)
