0.0.x
-----

* Bug fixes:
    - resolves 'zstd::libzstd' link target not found … when 'zstdTargets.cmake' exists (issue: #10)
    - resolves cmake 'FetchContent_MakeAvailable(mcap)' untarring path variance (issue: #11)
    - resolves absense of some mcap_build test project to confirm a "successful" install (issue: #12)
    - resolves lack of dependency info propagating to a consuming (e.g. test) project (issue: #13)
    - resolves lack of pkgconfig fallback when (LZ4|zstd) cmake files not available (issue: #14)
* Improved code comments
* Test added
    - `mcap_builder_check` provides a basic minimal test to check if a "successful" `mcap_builder` install is usable.
* Updates
    - Copyrights updated for 2025
    - Updated MCAP version from "1.4.0" to "1.4.1" (Issue #9)
