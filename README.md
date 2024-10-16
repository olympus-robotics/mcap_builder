# MCAP CMake Builder

This repo provides a wrapper to build and install [MCAP](https://github.com/foxglove/mcap) via CMake.

## Build and Install

To build and install run:
```bash
$ cd mcap_builder
$ mkdir build && cd build
$ cmake ../ && make install
```
you can change the install folder by setting `CMAKE_INSTALL_PREFIX` (as for any CMake project).

## Usage
### MCAP Is Installed
If you built and installed as described above, to include MCAP in your library first you need to add it to your CMake:
```cmake
find_package(mcap)

target_link_libraries(<target> PUBLIC mcap)
```

and in your code, you can include `reader.hpp` or `writer.hpp`. 

### Build MCAP Locally
If you do not want to install MCAP, and you want to build it as part of your project you can, in your `CMakeLists.txt` add:
```cmake
include(FetchContent)
FetchContent_Declare(
  mcap_builder
  GIT_REPOSITORY https://github.com/olympus-robotics/mcap_builder.git
  GIT_TAG main
)
FetchContent_MakeAvailable(mcap_builder)

# create your targets

target_link_libraries(<target> PUBLIC mcap)
```

### Macros
* Do not add `MCAP_IMPLEMENTATION` macro, as that is handled for you by this wrapper.
* This Cmake wrapper automatically detects if `LZ4` and `zstd` are available, and
  * if present, links them to the `mcap` library
  * if they are not present automatically define `MCAP_COMPRESSION_NO_LZ4` and `MCAP_COMPRESSION_NO_ZSTD` 

## Notes
MCAP is natively a header-only library, but in this wrapper, it is built into a binary library. 

This has two benefits:
* it allows to improve the compilation time of your project
* simplify its usage, by removing the need to specify any macros (see the section above).

The CMake option `MCAP_BUILDER_BUILD_SHARED_LIB` can be used to control the library type:

* If enabled (default), the library type will be `SHARED`
* If disabled, the library will depend on the value of the `BUILD_SHARED_LIBS` variable
