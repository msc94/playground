add_library (libgb
    rom.hpp
    rom.cpp
    gb.hpp
    gb.cpp
    memory.hpp
    memory.cpp
    cpu.hpp
    cpu.cpp
    opcodes.hpp
    opcodes.cpp
)

target_link_libraries (libgb LINK_PUBLIC libutils)

target_include_directories (libgb PUBLIC ../)
