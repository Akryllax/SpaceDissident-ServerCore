# CMakeList.txt : CMake project for GameServerCore0, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project ("GameServerCore0")

################################################################################
# Add Boost library

find_package(Boost 1.40.0 REQUIRED system)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()
################################################################################

################################################################################
# enable testing functionality
enable_testing()
################################################################################

################################################################################
option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." FALSE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()
################################################################################

################################################################################
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

function (AddCommonIncludesToTarget Collection Visibility)
  target_include_directories(${Collection} ${Visibility} "core")
  target_include_directories(${Collection} ${Visibility} "decorator")
  target_include_directories(${Collection} ${Visibility} "include")
  target_include_directories(${Collection} ${Visibility} "include/spdlog/include")
  target_include_directories(${Collection} ${Visibility} "message")
  target_include_directories(${Collection} ${Visibility} "network")
  target_include_directories(${Collection} ${Visibility} "util")
  target_include_directories(${Collection} ${Visibility} "world")
  target_include_directories(${Collection} ${Visibility} Boost::system)
endfunction()


# Add source to this project's executable.
set(SOURCES
  "core/server_core.cpp"
  "core/game_session.cpp"
  "util/config_reader.cpp"
  "util/config_holder.cpp"
  "decorator/base_decorator.cpp"
  "decorator/debug_decorator.cpp"
  "message/base_message.cpp"
  "core/modules/test_core_module.cpp"
)
################################################################################

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pragma-once-outside-header")
# set(CMAKE_BUILD_TYPE Debug)

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
  ${SOURCES}
)

AddCommonIncludesToTarget(GameServerCore0 PUBLIC)

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
include("CMakeLists_GTEST.txt")

include("CMakeLists.txt.test")

################################################################################
#                      Copy dynamic libs after build                           #
################################################################################

if (WIN32)
  add_custom_command(TARGET GameServerCore0 POST_BUILD                          # Adds a post-build event to GameServerCore0
      COMMAND ${CMAKE_COMMAND} -E copy_if_different                             # which executes "cmake - E copy_if_different..."
          "${PROJECT_SOURCE_DIR}/build/lib/networklib/NetworkLibrary.dll"       # <--this is in-file
          $<TARGET_FILE_DIR:GameServerCore0>)                                   # <--this is out-file pat
  add_custom_command(TARGET GameServerCore0 POST_BUILD                          # Adds a post-build event to GameServerCore0
      COMMAND ${CMAKE_COMMAND} -E copy_if_different                             # which executes "cmake - E copy_if_different..."
          "${PROJECT_SOURCE_DIR}/build/lib/test/TestLibrary.dll"                # <--this is in-file
          $<TARGET_FILE_DIR:GameServerCore0>)                                   # <--this is out-file path
elseif(UNIX)
  add_custom_command(TARGET GameServerCore0 POST_BUILD                          # Adds a post-build event to GameServerCore0
      COMMAND ${CMAKE_COMMAND} -E copy_if_different                             # which executes "cmake - E copy_if_different..."
          "${PROJECT_SOURCE_DIR}/build/lib/libNetworkLibrary.so"                # <--this is in-file
          $<TARGET_FILE_DIR:GameServerCore0>)                                   # <--this is out-file pat
  add_custom_command(TARGET GameServerCore0 POST_BUILD                          # Adds a post-build event to GameServerCore0
      COMMAND ${CMAKE_COMMAND} -E copy_if_different                             # which executes "cmake - E copy_if_different..."
          "${PROJECT_SOURCE_DIR}/build/lib/libTestLibrary.so"                   # <--this is in-file
          $<TARGET_FILE_DIR:GameServerCore0>)                                   # <--this is out-file path
endif()