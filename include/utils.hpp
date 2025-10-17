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

/*
 * @brief Retrieves all file names in a given folder with the specified extension.
 *
 * This function iterates through all regular files in the specified directory
 * and collects those whose extension matches the given format (e.g., "mtx").
 *
 * @param folder - the path to the folder to search in.
 * @param format - the file extension to filter by (without the dot)
 * @return Vector<String> - contains full paths to all matching files
 */
Vector<String> getFileNames(const String& folder, const String& format);

/*
 * @brief Generates a random permutation of integers in the range [0, n).
 *
 * This function creates a sequence of integers from 0 to n-1
 * and shuffles it using a random number generator based on std::mt19937.
 *
 * @param n - the size of the permutation
 * @return Vector<int_t> - contains the shuffled sequence
 */
Vector<int_t> getRandomPermutation(int_t n);