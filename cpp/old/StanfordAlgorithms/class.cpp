#include "class.hpp"

#include <string>
#include <iostream>

struct MyClass::MyClassPrivate {
    int value;
};

MyClass::MyClass(int value)
    : _impl(std::make_unique<MyClassPrivate>()) {
    _impl->value = value;
}

MyClass::MyClass(const MyClass &) = default;
MyClass::MyClass(MyClass &&) = default;
MyClass &MyClass::operator=(const MyClass &) = default;
MyClass &MyClass::operator=(MyClass &&) = default;

MyClass::~MyClass() = default;

std::string MyClass::get_value() {
    std::cout << &_impl << "\n";
    return std::to_string(_impl->value);
    std::remove_reference<int &>::type;
}
