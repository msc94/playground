add_executable (appttf 
    main.cpp
)

target_link_libraries (appttf LINK_PUBLIC libttf)
target_link_libraries (appttf LINK_PUBLIC libutils)

target_include_directories (appttf PUBLIC ../)