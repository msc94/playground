add_library (libgba SHARED
    rom.cpp
    gba.cpp
    memory.cpp
    cpu.cpp
)

target_link_libraries (libgba LINK_PUBLIC libutils)

target_include_directories (libgba PUBLIC ../)
