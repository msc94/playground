add_executable (emulator 
    main.cpp
)

target_link_libraries (emulator LINK_PUBLIC libgb)
target_link_libraries (emulator LINK_PUBLIC libutils)

target_include_directories (emulator PUBLIC ../)