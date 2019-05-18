# CMake 3.8 required for 17 to be a valid value for CXX_STANDARD
cmake_minimum_required(VERSION 3.8)

project(prometry)

option(PROMETRY_WARNINGS_AS_ERRORS "Warnings as errors" ON)

# Set hard requirements for C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Disable in-source builds
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif()

if (MSVC)
    if (PROMETRY_WARNINGS_AS_ERRORS)
        set(PROMETRY_CXX_FLAGS "/WX")
    endif()
else()
    if (PROMETRY_WARNINGS_AS_ERRORS)
        set(PROMETRY_CXX_FLAGS "-Werror")
    endif()
endif()

add_subdirectory(src)
