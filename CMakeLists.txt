cmake_minimum_required(VERSION 3.9)

include("${CMAKE_SOURCE_DIR}/cmake/HunterGate.cmake")
# Enable ExternalProject CMake module
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.23.11.tar.gz"
        SHA1 "b732407d782459f89950ab52bc0ff9612f3e4be2"
)

#
# Locate the clang-tidy executable and set variable CLANG_TIDY_EXE
#
find_program(
        CLANG_TIDY_EXE
        NAMES "clang-tidy"
        DOC "Path to clang-tidy executable"
)
if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-clang-analyzer-alpha.*")
endif()


# Main project definition
#
project(acropolis VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(TestBigEndian)
include(CTest)

set(SOURCE_FILES
        src/necv60/necv60.cpp src/necv60/necv60.h
        )

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/src/link.T")
add_library(acropolis SHARED ${SOURCE_FILES})

configure_file(src/config.h.in ${CMAKE_BINARY_DIR}/generated/config.h)
include_directories(${CMAKE_BINARY_DIR}/generated/)

TEST_BIG_ENDIAN(IS_BIG_ENDIAN)

if (IS_BIG_ENDIAN)
    add_definitions(-D__MSB_FIRST)
endif()

# custom options for MacOS
if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.7")
endif()

# Add a DEBUG flag when compiling in Debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()


# tests
# Enable and run the tests, for MSVC use a static version of the library
#
if(NOT SKIP_TESTS)
    if (MSVC)
        add_library(acropolis_static STATIC ${SOURCE_FILES})
    endif()
    enable_testing()
    add_subdirectory(tests)
endif()


# clang_tidy
# A target for compiling acropolis with clang and
# running clang-tidy to check for static analysis errors and warnings
#
if(CLANG_TIDY_EXE)
    Message("Enabling clang_tidy")
    add_library(clang_tidy STATIC ${SOURCE_FILES})
    if (MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
    endif()

    set (CLANG_TIDY_CHECKS "-checks=*,-clang-analyzer-alpha.*")
    set (DO_CLANG_TIDY, "${DO_CLANG_TIDY} ${CLANG_TIDY_CHECKS}")

    set_target_properties(
            clang_tidy PROPERTIES
            CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
    )
endif()
