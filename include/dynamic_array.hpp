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
    size_type cap = 0;
    pointer data_ptr = nullptr;

public:

    DynamicArray() = default;

    explicit DynamicArray(size_type n):
        sz(n),
        cap(n),
        data_ptr(new value_type[n]())
    {}

    DynamicArray(size_type n, const value_type& value):
        sz(n),
        cap(n),
        data_ptr(new value_type[n])
    {
        std::fill(data_ptr, data_ptr + sz, value);
    }

    DynamicArray(const DynamicArray& other):
        sz(other.sz),
        cap(other.cap),
        data_ptr(new value_type[other.sz])
    {
        std::copy(other.data_ptr, other.data_ptr + sz, data_ptr);
    }

    DynamicArray(DynamicArray&& other) noexcept:
        sz(other.sz),
        cap(other.cap),
        data_ptr(other.data_ptr)
    {
        other.sz = 0;
        other.cap = 0;
        other.data_ptr = nullptr;
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data_ptr;

            sz = other.sz;
            cap = other.cap;

            data_ptr = new value_type[cap];
            std::copy(other.data_ptr, other.data_ptr + sz, data_ptr);
        }
        return *this;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data_ptr;

            sz = other.sz;
            cap = other.cap;

            data_ptr = other.data_ptr;

            other.sz = 0;
            other.cap = 0;
            other.data_ptr = nullptr;
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
        if (n > cap) {
            value_type* new_data_ptr = new value_type[n]();

            std::copy(data_ptr, data_ptr + sz, new_data_ptr);
            delete[] data_ptr;

            cap = n;
            data_ptr = new_data_ptr;
        }

        sz = n;
    }

    void resize(size_type n, const value_type& value) {

        if (n > cap) {
            value_type* new_data_ptr = new value_type[n]();

            std::copy(data_ptr, data_ptr + sz, new_data_ptr);
            delete[] data_ptr;

            cap = n;
            data_ptr = new_data_ptr;
        }

        size_type copy_size = std::min(sz, n);
        for (size_type i = copy_size; i < n; ++i) {
            data_ptr[i] = value;
        }

        sz = n;
    }

    void assign(size_type n, const value_type& value) {
        if (n > cap) {
            cap = n;

            delete[] data_ptr;
            data_ptr = new value_type[n]();
        }

        sz = n;
        std::fill(data_ptr, data_ptr + n, value);
    }

    void clear() noexcept {
        delete[] data_ptr;

        sz = 0;
        cap = 0;
        data_ptr = nullptr;
    }

    void reserve(size_type new_cap) {
        if (new_cap > cap) {
            value_type* new_data_ptr = new value_type[new_cap];

            std::move(data_ptr, data_ptr + sz, new_data_ptr);

            delete[] data_ptr;
            data_ptr = new_data_ptr;
            cap = new_cap;
        }
    }

    void push_back(const value_type& value) {
        if (sz == cap) {
            reserve(cap * 2 + 1);
        }
        data_ptr[sz] = value;
        ++sz;
    }

    size_type capacity() const noexcept {
        return cap;
    }

    bool operator==(const DynamicArray& other) const noexcept {
        if (sz != other.sz) {
            return false;
        }
        for (size_type i = 0; i < sz; i++) {
            if (!(data_ptr[i] == other.data_ptr[i])) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const DynamicArray& other) const noexcept {
        return !(*this == other);
    }

    T& back() {
        return data_ptr[sz - 1];
    }

    const T& back() const{
        return data_ptr[sz - 1];
    }
};
