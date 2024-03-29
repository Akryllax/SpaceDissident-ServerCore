SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++ )
SET(CMAKE_FIND_ROOT_PATH  /etc/alternatives /usr/bin)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

ADD ./cmake_toolchains/clang.cmake /clang.cmake
