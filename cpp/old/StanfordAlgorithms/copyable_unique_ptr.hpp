#pragma once

#include <memory>

template <typename T>
class copyable_unique_ptr {
private:
    std::unique_ptr<T> _ptr;

public:
    copyable_unique_ptr(std::unique_ptr<T> &&ptr)
        : _ptr(std::move(ptr)) {}

    ~copyable_unique_ptr() = default;

    copyable_unique_ptr(const copyable_unique_ptr<T> &other) {
        _ptr = std::make_unique<T>(*other._ptr);
    }

    copyable_unique_ptr(copyable_unique_ptr<T> &&other) {
         _ptr = std::move(other._ptr);
    }

    copyable_unique_ptr &operator=(const copyable_unique_ptr<T> &other) {
        _ptr = std::make_unique<T>(*other._ptr);
    }

    copyable_unique_ptr &operator=(copyable_unique_ptr<T> &&other) {
         _ptr = std::move(other._ptr);
    }

    T *operator->() {
        return _ptr.get();
    }
};
