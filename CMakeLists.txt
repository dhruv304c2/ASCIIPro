set(CMAKE_VERBOSE_MAKEFILE ON)
# Minimum required version of CMake
cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")

# Compile commands for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project name and version
project(GameProject VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Final step: Place the executable and resources in the game folder
add_custom_target(
    resource_copy ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/game/resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/game/resources/
    COMMENT "copying resources to game folder"
)

# Add source files
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add the executable
add_executable(game ${SRC_FILES})

# target dependencies
add_dependencies(game resource_copy)

add_custom_command(
    TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/game/bin
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:game> ${CMAKE_BINARY_DIR}/game/bin/
)

#============VENDORS=============================
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

list(APPEND CMAKE_SYSTEM_PREFIX_PATH 
    "${CMAKE_SOURCE_DIR}/vendor/icu"
)
set(ICU_USE_STATIC_LIBS ON)
find_package(ICU REQUIRED)
if (ICU_FOUND)
    include_directories(${ICU_INCLUDE_DIRS})
    target_link_libraries(game PRIVATE ${ICU_LIBRARIES})

    if (ICU_I18N_FOUND)
        target_link_libraries(game PRIVATE ${ICU_I18N_LIBRARIES})
    endif()
endif()

#============VENDORS=============================

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#target include dirs
target_include_directories(game PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

get_target_property(INCLUDE_DIRS game INCLUDE_DIRECTORIES)
message(STATUS "Target include directories: ${INCLUDE_DIRS}")

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

if (WIN32)
    target_compile_options(game PUBLIC 
        -std=c++17
    )
elseif (UNIX)
    target_compile_options(game PUBLIC 
        -fexec -charset=UTF-8
    )
endif()

