# CMakeList.txt : CMake project for GameServerCore0, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project ("TestLibrary")

add_library(TestLibrary SHARED "test_library.cpp")
target_include_directories(TestLibrary PUBLIC "")

target_compile_definitions(TestLibrary PRIVATE BUILDING_DLL=1)
