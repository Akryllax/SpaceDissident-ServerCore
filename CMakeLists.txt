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
  "world/common/data_holder.h"
  "world/math/Color.h"
  "world/math/Matrix3.h"
  "world/math/Matrix4.h"
  "world/math/Vector2.h"
  "world/math/Vector3.h"
  "world/math/Vector4.h"
  "world/math/transform.h"
  "world/common/gameobject.h"
  )

# Add lib/test subdirectory into CMake context
add_subdirectory("lib/test" TestLibrary)
add_subdirectory("lib/networklib" NetworkLibrary)
include_directories("${PROJECT_SOURCE_DIR}/lib/test")
include_directories("${PROJECT_SOURCE_DIR}/lib/networklib")

################################################################################
#                          MAIN BINARY                                         #
################################################################################
add_executable (GameServerCore0
  "GameServerCore0.cpp"
  "GameServerCore0.h"
  ${SOURCES}
)
target_include_directories(GameServerCore0 PUBLIC "include")
target_include_directories(GameServerCore0 PUBLIC "message")
target_include_directories(GameServerCore0 PUBLIC "core")
target_include_directories(GameServerCore0 PUBLIC "decorator")
target_include_directories(GameServerCore0 PUBLIC "world")

# Link TestLibrary
message("-- Linking TestLibrary")
target_link_libraries(GameServerCore0 PRIVATE TestLibrary)
# Link TestLibrary
message("-- Linking NetworkLibrary")
target_link_libraries(GameServerCore0 PRIVATE NetworkLibrary)

# TODO: Add tests and install targets if needed.

################################################################################
#            GTEST                                                             #
################################################################################

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

################################################################################
#                   DEFINE GTEST BINARIES                                      #
################################################################################

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(core_gtest test/basic_test.cpp ${SOURCES})

target_include_directories(core_gtest PRIVATE "include")
target_include_directories(core_gtest PRIVATE "core")
target_include_directories(core_gtest PRIVATE "message")
target_include_directories(core_gtest PRIVATE "decorator")
target_include_directories(core_gtest PRIVATE "world")
target_link_libraries(core_gtest gtest_main)
# Link TestLibrary
message("-- Linking TestLibrary")
target_link_libraries(core_gtest TestLibrary)
add_test(NAME core_gtest_test COMMAND core_gtest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(world_gtest test/world_test.cpp ${SOURCES})

target_include_directories(world_gtest PRIVATE "include")
target_include_directories(world_gtest PRIVATE "core")
target_include_directories(world_gtest PRIVATE "message")
target_include_directories(world_gtest PRIVATE "decorator")
target_include_directories(world_gtest PRIVATE "world")
target_link_libraries(world_gtest gtest_main)
# Link TestLibrary
message("-- Linking TestLibrary")
target_link_libraries(world_gtest TestLibrary)
add_test(NAME world_gtest_test COMMAND world_gtest)


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(gameobject_test test/gameobject_test.cpp ${SOURCES})

target_include_directories(gameobject_test PRIVATE "include")
target_include_directories(gameobject_test PRIVATE "core")
target_include_directories(gameobject_test PRIVATE "message")
target_include_directories(gameobject_test PRIVATE "decorator")
target_include_directories(gameobject_test PRIVATE "world")
target_link_libraries(gameobject_test gtest_main)
# Link TestLibrary
message("-- Linking TestLibrary")
target_link_libraries(gameobject_test TestLibrary)
add_test(NAME gameobject_test_test COMMAND gameobject_test)


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(networklib_test test/networklib_test.cpp ${SOURCES})

target_include_directories(networklib_test PRIVATE "include")
target_include_directories(networklib_test PRIVATE "core")
target_include_directories(networklib_test PRIVATE "message")
target_include_directories(networklib_test PRIVATE "decorator")
target_include_directories(networklib_test PRIVATE "world")
target_link_libraries(networklib_test gtest_main)
# Link TestLibrary
message("-- Linking NetworkLibrary")
target_link_libraries(networklib_test NetworkLibrary)
add_test(NAME networklib_test_test COMMAND networklib_test)

################################################################################
#           PROTOBUF                                                           #
################################################################################

# # Add googletest directly to our build. This defines
# # the gtest and gtest_main targets.
# add_subdirectory(${PROJECT_SOURCE_DIR}/tools/protobuf-3.15.5/cmake
#                  EXCLUDE_FROM_ALL)


################################################################################
#                      Copy DLLs after build                                   #
################################################################################
add_custom_command(TARGET GameServerCore0 POST_BUILD                   # Adds a post-build event to GameServerCore0
    COMMAND ${CMAKE_COMMAND} -E copy_if_different                      # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/build/lib/networklib/NetworkLibrary.dll"# <--this is in-file
        $<TARGET_FILE_DIR:GameServerCore0>)                            # <--this is out-file pat
add_custom_command(TARGET GameServerCore0 POST_BUILD                   # Adds a post-build event to GameServerCore0
    COMMAND ${CMAKE_COMMAND} -E copy_if_different                      # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/build/lib/test/TestLibrary.dll"         # <--this is in-file
        $<TARGET_FILE_DIR:GameServerCore0>)                            # <--this is out-file path