cmake_minimum_required(VERSION 3.14)
project(autodrive_examples_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVC: treat source files as UTF-8
if(MSVC)
    add_compile_options(/utf-8)
endif()

# ── Pull metacar C++ API via FetchContent ──────────────────────────
include(FetchContent)
FetchContent_Declare(
    metacar
    GIT_REPOSITORY https://github.com/YDL-Simulation/autodrive_api_cpp.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(metacar)

# ── Examples ───────────────────────────────────────────────────────
add_subdirectory(src)
