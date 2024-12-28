
# Minimum required version of CMake
cmake_minimum_required(VERSION 3.15)

# Compile commands for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project name and version
project(GameProject VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)

#========Include Dependencies=============f

#FTXUI
include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

#==========================================

# Add link libraries
set(LINKS 
    ftxui::screen 
    ftxui::dom 
    ftxui::component
)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add the executable
add_executable(game ${SRC_FILES})

# Link ftxui to the game executable
target_link_libraries(game PRIVATE ${LINKS})

# Add Compiler flags

if (WIN32)
    target_compile_options(game PRIVATE
        -std=c++17
    )
elseif (UNIX)
    target_compile_options(game PRIVATE
        -fexec -charset=UTF-8
    )
endif()

# Enable warnings
# if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     target_compile_options(game PRIVATE -Wall -Wextra -pedantic)
# endif()
#
# if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#     target_compile_options(game PRIVATE /W4 /permissive-)
# endif()

# Copy resources to the build directory
add_custom_target(
    copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
)
add_dependencies(game copy_resources)

# Final step: Place the executable and resources in the game folder
add_custom_command(
    TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/game/resources
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/game/target
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:game> ${CMAKE_BINARY_DIR}/game/target/
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources ${CMAKE_BINARY_DIR}/game/resources/
)

