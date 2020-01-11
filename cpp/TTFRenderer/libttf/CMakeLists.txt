add_library (libttf SHARED
    ttf_file.cpp
)

target_link_libraries (libttf LINK_PUBLIC libutils)

target_include_directories (libttf PUBLIC ../)
