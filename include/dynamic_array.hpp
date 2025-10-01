#pragma once

#include <algorithm>

template <typename T>
class DynamicArray {
public:

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;

private:

    size_type sz = 0;
    pointer data_ptr = nullptr;

public:

    DynamicArray() = default;

    explicit DynamicArray(size_type n):
        data_ptr(new value_type[n]()),
        sz(n)
    {

    }

    DynamicArray(size_type n, const value_type& value):
        data_ptr(new value_type[n]),
        sz(n)
    {
        std::fill(data_ptr, data_ptr + sz, value);
    }

    DynamicArray(const DynamicArray& other):
        data_ptr(new value_type[other.sz]),
        sz(other.sz)
    {
        std::copy(other.data_ptr, other.data_ptr + sz, data_ptr);
    }

    DynamicArray(DynamicArray&& other) noexcept:
        data_ptr(other.data_ptr),
        sz(other.sz)
    {
        other.data_ptr = nullptr;
        other.sz = 0;
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data_ptr;

            sz = other.sz;
            data_ptr = new value_type[sz];
            std::copy(other.data_ptr, other.data_ptr + sz, data_ptr);
        }
        return *this;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data_ptr;

            data_ptr = other.data_ptr;
            sz = other.sz;

            other.data_ptr = nullptr;
            other.sz = 0;
        }
        return *this;
    }

    ~DynamicArray() {
        delete[] data_ptr;
    }

    reference operator[](size_type i) noexcept {
        return data_ptr[i];
    }

    const_reference operator[](size_type i) const noexcept {
        return data_ptr[i];
    }

    pointer data() noexcept {
        return data_ptr;
    }

    const_pointer data() const noexcept {
        return data_ptr;
    }

    size_type size() const noexcept {
        return sz;
    }

    bool empty() const noexcept {
        return sz == 0;
    }

    iterator begin() noexcept {
        return data_ptr;
    }

    iterator end() noexcept {
        return data_ptr + sz;
    }

    const_iterator begin() const noexcept {
        return data_ptr;
    }

    const_iterator end() const noexcept {
        return data_ptr + sz;
    }

    void resize(size_type n) {
        value_type* new_data_ptr = new value_type[n]();
        size_type copy_size = std::min(sz, n);

        std::copy(data_ptr, data_ptr + copy_size, new_data_ptr);
        delete[] data_ptr;

        data_ptr = new_data_ptr;
        sz = n;
    }

    void resize(size_type n, const value_type& value) {
        value_type* new_data_ptr = new value_type[n]();
        size_type copy_size = std::min(sz, n);

        std::copy(data_ptr, data_ptr + copy_size, new_data_ptr);
        for (size_type i = copy_size; i < n; ++i) {
            new_data_ptr[i] = value;
        }
        delete[] data_ptr;

        data_ptr = new_data_ptr;
        sz = n;
    }

    void assign(size_type n, const value_type& value) {
        delete[] data_ptr;

        sz = n;
        data_ptr = new value_type[n]();
        std::fill(data_ptr, data_ptr + n, value);
    }

    void clear() noexcept {
        delete[] data_ptr;

        data_ptr = nullptr;
        sz = 0;
    }
};
