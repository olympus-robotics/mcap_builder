add_library(mcap SHARED lib.cpp)

target_include_directories(mcap PUBLIC
  $<BUILD_INTERFACE:${MCAP_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include/>
)

set(DEPENDENCIES "")

find_package(lz4 QUIET)
if (${lz4_FOUND})
  message(STATUS "Found lz4 from ${lz4_DIR}")
  list(APPEND DEPENDENCIES LZ4::lz4)
else()
  message(WARNING "Dependency LZ4 not found, disabling")
  target_compile_definitions(mcap PUBLIC "MCAP_COMPRESSION_NO_LZ4")
endif()

find_package(zstd QUIET)
if (${zstd_FOUND})
  message(STATUS "Found zstd from ${zstd_DIR}")
  list(APPEND DEPENDENCIES zstd::libzstd)
else()
  message(WARNING "Dependency zstd not found, disabling")
  target_compile_definitions(mcap PUBLIC "MCAP_COMPRESSION_NO_ZSTD")
endif()

target_link_libraries(mcap PUBLIC ${DEPENDENCIES})
