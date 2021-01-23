# CMakeList.txt : CMake project for GameServerCore0, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project ("GameServerCore0")

# Add source to this project's executable.
set(SOURCES
  "core/server_core.h"
  "core/server_core.cpp"
  "util/core_timer.h"
  "core/game_session.h"
  "core/game_session.cpp"
  "util/config_reader.h"
  "util/config_reader.cpp"
  "decorator/base_decorator.h"
  "decorator/base_decorator.cpp"
  "decorator/debug_decorator.h"
  "decorator/debug_decorator.cpp"
  "message/base_message.h"
  "message/base_message.cpp"
  "message/message_type_id.h"
  )

add_executable (GameServerCore0 "GameServerCore0.cpp" "GameServerCore0.h" ${SOURCES})

target_include_directories(GameServerCore0 PRIVATE "include")
target_include_directories(GameServerCore0 PRIVATE "message")
target_include_directories(GameServerCore0 PRIVATE "core")
target_include_directories(GameServerCore0 PRIVATE "decorator")

# TODO: Add tests and install targets if needed.

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(core_gtest test/basic_test.cpp ${SOURCES})

target_include_directories(core_gtest PRIVATE "include")
target_include_directories(core_gtest PRIVATE "core")
target_include_directories(core_gtest PRIVATE "message")
target_include_directories(core_gtest PRIVATE "decorator")
target_link_libraries(core_gtest gtest_main)
add_test(NAME core_gtest_test COMMAND core_gtest)
