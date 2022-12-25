# CMakeList.txt : CMake project for GameServerCore0, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
)
project("NetworkLibrary" LANGUAGES CXX)

add_library(NetworkLibrary SHARED "networklib.cpp" ${SOURCES})

target_include_directories(NetworkLibrary PUBLIC "")
target_include_directories(NetworkLibrary PUBLIC "session")
target_include_directories(NetworkLibrary PUBLIC "socket")

target_compile_definitions(NetworkLibrary PRIVATE BUILDING_DLL=1)
