# CMake 3.8 required for 17 to be a valid value for CXX_STANDARD
cmake_minimum_required(VERSION 3.8)

project(prometry)

option(PROMETRY_WARNINGS_AS_ERRORS "Warnings as errors" ON)

# Sanity check : Check that all submodules are present
# =======================================================================

function(check_submodules_present)
    file(READ "${PROJECT_SOURCE_DIR}/.gitmodules" gitmodules)
    string(REGEX MATCHALL "path *= *[^ \t\r\n]*" gitmodules ${gitmodules})
    foreach(module ${gitmodules})
        string(REGEX REPLACE "path *= *" "" module ${module})
        if (NOT EXISTS "${PROJECT_SOURCE_DIR}/${module}/.git")
            message(SEND_ERROR "Git submodule ${module} not found."
                    "Please run: git submodule update --init --recursive")
        endif()
    endforeach()
endfunction()
check_submodules_present()

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

# System imported libraries
# ======================
find_package(SymEngine REQUIRED)

enable_testing()
add_subdirectory(externals)
add_subdirectory(src)
