# MCAP CMake Builder

This repo provide a wrapper to build and install [MCAP](https://github.com/foxglove/mcap) via CMake.

## Build

To build and install run:
```bash
$ cd mcap_build
$ mkdir build && cd build
$ cmake ../ && make install
```
you can change the install folder by setting `CMAKE_INSTALL_PREFIX` (as for any CMake project). 

## Usage
### MCAP Is Installed
To include MCAP in your library first you need to add it to your CMake:
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
)
FetchContent_MakeAvailable(mcap_builder)

# create your targets

target_link_libraries(<target> PUBLIC mcap)
```

### Macros
* Do not add `MCAP_IMPLEMENTATION` macro, as that is handled for you by this wrapper.
* This Cmake wrapper automatically detect if `LZ4` and `zstd` are available, and
  * if present, links them to the `mcap` library
  * if they are not present automatically define `MCAP_COMPRESSION_NO_LZ4` and `MCAP_COMPRESSION_NO_ZSTD` 





