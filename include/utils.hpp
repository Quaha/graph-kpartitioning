#pragma once

#include <vector>
#include <string>
#include <filesystem>

using int_t = long long;
using real_t = long double;

inline constexpr real_t EPS = 1e-8;

template <typename T> 
using Vector = std::vector<T>;

using String = std::string;

Vector<String> getFileNames(const String& folder, const String& format);