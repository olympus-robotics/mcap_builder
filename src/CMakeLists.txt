# =================================================================================================
#  Copyright (C) 2023-2025 MCAP_BUILDER Contributors
# =================================================================================================
# FILE: mcap_builder  src/CMakeLists.txt

add_library(mcap lib.cpp)

target_include_directories(mcap PUBLIC
  $<BUILD_INTERFACE:${MCAP_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include/>
)

set(DEPENDENCIES "")

# Find lz4
find_package(lz4 QUIET)
if (${lz4_FOUND})
  message(STATUS "Found lz4 from ${lz4_DIR}")
  set(MCAP_LZ4_VIA_PKGCONFIG FALSE PARENT_SCOPE)
  if (TARGET LZ4::lz4)
    set(MCAP_LZ4_FOUND TRUE PARENT_SCOPE)
    list(APPEND DEPENDENCIES LZ4::lz4)
  else()
    message(WARNING "LZ4::lz4 not found, disabling lz4")
    set(MCAP_LZ4_FOUND FALSE PARENT_SCOPE)
    target_compile_definitions(mcap PUBLIC "MCAP_COMPRESSION_NO_LZ4")
  endif()
else()
  # Fallback to pkg-config for lz4
  find_package(PkgConfig QUIET)
  if (PkgConfig_FOUND)
    pkg_check_modules(LZ4 QUIET liblz4)
    if (LZ4_FOUND)
      message(STATUS "Found lz4 via pkg-config")
      set(MCAP_LZ4_FOUND TRUE PARENT_SCOPE)
      set(MCAP_LZ4_VIA_PKGCONFIG TRUE PARENT_SCOPE)
      # Create an imported target for lz4
      if(NOT TARGET LZ4::lz4)
        add_library(LZ4::lz4 INTERFACE IMPORTED)
        set_target_properties(LZ4::lz4 PROPERTIES
          INTERFACE_INCLUDE_DIRECTORIES "${LZ4_INCLUDE_DIRS}"
          INTERFACE_LINK_LIBRARIES "${LZ4_LINK_LIBRARIES}"
        )
      endif()
      list(APPEND DEPENDENCIES LZ4::lz4)
    else()
      message(WARNING "LZ4 not found via pkg-config, disabling")
      set(MCAP_LZ4_FOUND FALSE PARENT_SCOPE)
      set(MCAP_LZ4_VIA_PKGCONFIG FALSE PARENT_SCOPE)
      target_compile_definitions(mcap PUBLIC "MCAP_COMPRESSION_NO_LZ4")
    endif()
  else()
    message(WARNING "Dependency LZ4 not found, pkg-config not available, disabling")
    set(MCAP_LZ4_FOUND FALSE PARENT_SCOPE)
    set(MCAP_LZ4_VIA_PKGCONFIG FALSE PARENT_SCOPE)
    target_compile_definitions(mcap PUBLIC "MCAP_COMPRESSION_NO_LZ4")
  endif()
endif()

# Find zstd
find_package(zstd QUIET)
if (${zstd_FOUND})
  message(STATUS "Found zstd from ${zstd_DIR}")
  set(MCAP_ZSTD_VIA_PKGCONFIG FALSE PARENT_SCOPE)
  # Check if zstd::libzstd exists, else fallback to zstd::libzstd_static
  if (TARGET zstd::libzstd)
    set(MCAP_ZSTD_FOUND TRUE PARENT_SCOPE)
    list(APPEND DEPENDENCIES zstd::libzstd)
  elseif (TARGET zstd::libzstd_static)
    set(MCAP_ZSTD_FOUND TRUE PARENT_SCOPE)
    list(APPEND DEPENDENCIES zstd::libzstd_static)
  else()
    message(WARNING "Neither zstd::libzstd nor zstd::libzstd_static found, disabling zstd")
    set(MCAP_ZSTD_FOUND FALSE PARENT_SCOPE)
    target_compile_definitions(mcap PUBLIC "MCAP_COMPRESSION_NO_ZSTD")
  endif()
else()
  # Fallback to pkg-config for zstd
  find_package(PkgConfig QUIET)
  if (PkgConfig_FOUND)
    pkg_check_modules(ZSTD QUIET libzstd)
    if (ZSTD_FOUND)
      message(STATUS "Found zstd via pkg-config")
      set(MCAP_ZSTD_FOUND TRUE PARENT_SCOPE)
      set(MCAP_ZSTD_VIA_PKGCONFIG TRUE PARENT_SCOPE)
      # Create an imported target for zstd
      if(NOT TARGET zstd::libzstd)
        add_library(zstd::libzstd INTERFACE IMPORTED)
        set_target_properties(zstd::libzstd PROPERTIES
          INTERFACE_INCLUDE_DIRECTORIES "${ZSTD_INCLUDE_DIRS}"
          INTERFACE_LINK_LIBRARIES "${ZSTD_LINK_LIBRARIES}"
        )
      endif()
      list(APPEND DEPENDENCIES zstd::libzstd)
    else()
      message(WARNING "ZSTD not found via pkg-config, disabling")
      set(MCAP_ZSTD_FOUND FALSE PARENT_SCOPE)
      set(MCAP_ZSTD_VIA_PKGCONFIG FALSE PARENT_SCOPE)
      target_compile_definitions(mcap PUBLIC "MCAP_COMPRESSION_NO_ZSTD")
    endif()
  else()
    message(WARNING "Dependency zstd not found, pkg-config not available, disabling")
    set(MCAP_ZSTD_FOUND FALSE PARENT_SCOPE)
    set(MCAP_ZSTD_VIA_PKGCONFIG FALSE PARENT_SCOPE)
    target_compile_definitions(mcap PUBLIC "MCAP_COMPRESSION_NO_ZSTD")
  endif()
endif()

target_link_libraries(mcap PUBLIC ${DEPENDENCIES})
