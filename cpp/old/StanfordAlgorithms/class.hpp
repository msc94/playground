#pragma once

#include <string>

#include "copyable_unique_ptr.hpp"

class MyClass {
private:
    struct MyClassPrivate;
    copyable_unique_ptr<MyClassPrivate> _impl;

public:
    MyClass(int value);

    MyClass(const MyClass &);
    MyClass(MyClass &&);
    MyClass &operator=(const MyClass &);
    MyClass &operator=(MyClass &&);
    ~MyClass();

    std::string get_value();
};
