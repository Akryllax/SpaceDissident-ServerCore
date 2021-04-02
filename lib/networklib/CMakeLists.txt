# CMakeList.txt : CMake project for GameServerCore0, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    "socket/basic_socket.h"
    "socket/tcp_socket.h"
    "socket/udp_socket.h"
    "session/network_session.h"
    "session/network_channel.h"
    "session/network_channel.cpp"
)
project("NetworkLibrary" LANGUAGES CXX)

add_library(NetworkLibrary SHARED "networklib.h" "networklib.cpp" ${SOURCES})
target_compile_definitions(NetworkLibrary PRIVATE BUILDING_DLL=1)
