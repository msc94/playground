cmake_minimum_required (VERSION 3.0)
project (GBEmulator)

# find_package (fmt CONFIG REQUIRED)
# link_libraries (fmt::fmt fmt::fmt-header-only)

find_package (spdlog CONFIG REQUIRED)
link_libraries (spdlog::spdlog spdlog::spdlog_header_only)

set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

add_subdirectory (app)
add_subdirectory (libgb)
add_subdirectory (libutils)
# add_subdirectory (test)
