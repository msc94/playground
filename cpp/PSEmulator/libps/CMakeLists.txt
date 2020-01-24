add_library (libps
    rom.hpp
    rom.cpp
    playstation.hpp
    playstation.cpp
    memory.hpp
    memory.cpp
    cpu.hpp
    cpu.cpp
    opcodes.hpp
    opcodes.cpp
)

target_link_libraries (libps LINK_PUBLIC libutils)

target_include_directories (libps PUBLIC ../)
