#pragma once

#include <vector>
#include <string>
#include <filesystem>

using int_t = long long;
using real_t = long double;

inline constexpr real_t EPS = 1e-8;

std::vector<std::string> getFileNames(const std::string& folder, const std::string& format);