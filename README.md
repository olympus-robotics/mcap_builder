# MCAP CMake Builder

This repo provides a wrapper to build and install [MCAP](https://github.com/foxglove/mcap) via CMake.

## Build, Install and Test

_Prerequisites_

```bash
# apt package manager
sudo apt install lz4 liblz4-dev zstd libzstd-dev

# homebrew package manager
brew install lz4 zstd
```

- `pkgconf` may also need to be install on some systems.


The current version of the `MCAP` C++ library can be double checked at [foxglove/mcap#developer-quick-start](https://github.com/foxglove/mcap#developer-quick-start) and updated in [CMakeLists.txt ](CMakeLists.txt) `set (VERSION …)` as needed.

To build and install run:

```bash
git clone git@github.com:olympus-robotics/mcap_builder.git
cd mcap_builder

mkdir build && cd build
cmake -S ../ -B . # -Wno-dev reduces CMake-developer-specific warnings clutter
sudo make install
```
you can change the install folder by setting `CMAKE_INSTALL_PREFIX` (as for any CMake project).

_Test: Check Installation Usability_

``` sh
cd test/mcap_builder_check
mkdir build && cd build
cmake -S ../ -B .
make
./mcap_builder_check
# Successfully included and used mcap library!
# LZ4: Not available
# ZSTD: Available
```

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
