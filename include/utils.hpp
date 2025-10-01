#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <random>
#include <numeric>

#include "dynamic_array.hpp"

using int_t = long long;
using real_t = long double;

inline constexpr real_t EPS = 1e-8;

template <typename T> 
using Vector = DynamicArray<T>;

using String = std::string;

Vector<String> getFileNames(const String& folder, const String& format);

Vector<int_t> getRandomPermutation(int_t n);