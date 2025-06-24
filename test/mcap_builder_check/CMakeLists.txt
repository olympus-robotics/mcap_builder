# =================================================================================================
#  Copyright (C) 2023-2025 MCAP_BUILDER Contributors
# =================================================================================================
# FILE: test/mcap_builder_check  CMakeLists.txt

cmake_minimum_required(VERSION 3.22.1)
project(mcap_builder_check LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Find the installed mcap package
find_package(mcap REQUIRED)

# Create an executable
add_executable(mcap_builder_check main.cpp)

# Link against the mcap library
target_link_libraries(mcap_builder_check PUBLIC mcap)
