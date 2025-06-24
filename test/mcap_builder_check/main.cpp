//=================================================================================================
// Copyright (C) 2023-2025 MCAP_BUILDER Contributors
//=================================================================================================
// FILE: mcap_builder_check  main.cpp

#include <mcap/mcap.hpp>
#include <iostream>

int main() {
    mcap::McapWriter writer;
    std::cout << "Successfully included and used mcap library!\n";
    #ifdef MCAP_COMPRESSION_NO_LZ4
    std::cout << "LZ4: Not available\n";
    #else
    std::cout << "LZ4: Available\n";
    #endif
    #ifdef MCAP_COMPRESSION_NO_ZSTD
    std::cout << "ZSTD: Not available\n";
    #else
    std::cout << "ZSTD: Available\n";
    #endif
    return 0;
}
