#pragma once

#include <vector>
#include <string>
#include <filesystem>

using idx_t = long long;
using real_t = long double;

inline constexpr real_t EPS = 1e-8;

std::vector<std::string> getMtxFileNames(const std::string& folder);