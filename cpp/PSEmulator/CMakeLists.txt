cmake_minimum_required (VERSION 3.0)
project (PSEmulator)

# find_package (fmt CONFIG REQUIRED)
# link_libraries (fmt::fmt fmt::fmt-header-only)

# find_package (spdlog CONFIG REQUIRED)
# link_libraries (spdlog::spdlog spdlog::spdlog_header_only)

set (CMAKE_STATIC_LIBRARY_PREFIX "")
set (CMAKE_SHARED_LIBRARY_PREFIX "")
 
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_EXECUTABLE_SUFFIX .html)
set (CMAKE_VERBOSE_MAKEFILE ON)

add_compile_options (-s DISABLE_EXCEPTION_CATCHING=0)

add_compile_options (-g4)
add_link_options (-g4)
add_link_options (--source-map-base http://localhost:8080/)

add_subdirectory (app)
add_subdirectory (libps)
add_subdirectory (libutils)
# add_subdirectory (test)
