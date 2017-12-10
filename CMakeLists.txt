cmake_minimum_required (VERSION 2.8)
project ("Branch Filesystem")

option(DEBUG "Builds BFS in debug mode (-g -O0)" off)

# Compile flags
set(C_FLAGS "-Wall -pedantic -std=c99 -O3")
set(C_FLAGS_DEBUG "-Wall -pedantic -std=c99 -g -O0 -DBFS_DEBUG")

# Build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (DEBUG)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS_DEBUG}")
else()
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS}")
endif()

if (WIN32)
  if (DEBUG)
    set(EXEC_NAME "bfs_debug.exe")
  else()
    set(EXEC_NAME "bfs.exe")
  endif()
elseif (UNIX)
  if (DEBUG)
    set(EXEC_NAME "bfs_debug.out")
  else()
    set(EXEC_NAME "bfs.out")
  endif()
endif()

set (SRC src/main.c
  src/bfs_macros.h
  src/bfs_cmdline.c
  src/bfs_cmdline.h
  src/bfs_string.c
  src/bfs_string.h
  src/bfs_node.c
  src/bfs_node.h
  src/bfs_tree.c
  src/bfs_tree.h
  src/bfs_errors.c
  src/bfs_errors.h
  src/bfs.c
  src/bfs.h
  )

add_executable(${EXEC_NAME} ${SRC})
