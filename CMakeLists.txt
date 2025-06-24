# =================================================================================================
#  Copyright (C) 2023-2025 MCAP_BUILDER Contributors
# =================================================================================================
# FILE: mcap_builder  CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)

# Define MCAP project version
# See: https://github.com/foxglove/mcap#developer-quick-start
set(VERSION "1.4.1")

project(mcap_builder LANGUAGES CXX VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.29")
  set(DOWNLOAD_EXTRACT_TIMESTAMP_ARG "DOWNLOAD_EXTRACT_TIMESTAMP;TRUE")
else()
  set(DOWNLOAD_EXTRACT_TIMESTAMP_ARG "")
endif()

# Define MCAP dependency tag and fetch it from GitHub as a tarball
set(MCAP_TAG "releases/cpp/v${VERSION}")
FetchContent_Declare(
  mcap
  URL https://github.com/foxglove/mcap/archive/refs/tags/${MCAP_TAG}.tar.gz
  ${DOWNLOAD_EXTRACT_TIMESTAMP_ARG}
  SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/mcap-src
)
FetchContent_MakeAvailable(mcap) # Download and populate MCAP dependencies

# Dynamically locate mcap.hpp to handle platform cmake directory variations
find_path(MCAP_INCLUDE_DIR
  NAMES mcap/mcap.hpp
  HINTS ${mcap_SOURCE_DIR}
  PATH_SUFFIXES cpp/mcap/include mcap-releases-cpp-v${VERSION}/cpp/mcap/include
  NO_DEFAULT_PATH
)
if(NOT MCAP_INCLUDE_DIR)
  message(FATAL_ERROR "mcap.hpp not found in ${mcap_SOURCE_DIR}")
endif()
message(STATUS "MCAP_INCLUDE_DIR set to ${MCAP_INCLUDE_DIR}")

# Delegate to src/CMakeLists.txt to build the mcap library and its dependencies
add_subdirectory(src)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/mcap-config-version.cmake"
    VERSION ${CMAKE_PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(TARGETS mcap
    EXPORT mcap-targets
    RUNTIME DESTINATION bin      # Executables go to bin/
    LIBRARY DESTINATION lib      # Shared libraries go to lib/
    ARCHIVE DESTINATION lib      # Static libraries go to lib/
    INCLUDES DESTINATION include # Headers tied to the target go to include/
)
install(DIRECTORY ${MCAP_INCLUDE_DIR}/mcap/ DESTINATION include/mcap)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/mcap-config.cmake.in"
    "${PROJECT_BINARY_DIR}/mcap-config.cmake"
    INSTALL_DESTINATION lib/cmake/mcap
    PATH_VARS MCAP_LZ4_FOUND MCAP_ZSTD_FOUND MCAP_LZ4_VIA_PKGCONFIG MCAP_ZSTD_VIA_PKGCONFIG
)

install(EXPORT mcap-targets DESTINATION lib/cmake/mcap)
install(FILES "${PROJECT_BINARY_DIR}/mcap-config-version.cmake"
              "${PROJECT_BINARY_DIR}/mcap-config.cmake"
        DESTINATION lib/cmake/mcap)
