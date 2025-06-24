# Readme: `mcap_builder_check`

```sh
cd test/mcap_builder_check

mkdir build
cd build
cmake -S ../ -B .

make VERBOSE=1
./mcap_builder_check
# Successfully included and used mcap library!
# LZ4: Not available
# ZSTD: Available
```

