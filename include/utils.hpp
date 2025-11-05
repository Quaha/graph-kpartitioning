#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <random>
#include <numeric>

#include "dynamic_array.hpp"

using int_t = long long;
using real_t = double;

inline constexpr real_t EPS = 1e-8;

template <typename T> 
using Vector = std::vector<T>;

using String = std::string;

/*
 * Retrieves all file names in a given folder with the specified extension.
 *
 * This function iterates through all regular files in the specified directory
 * and collects those whose extension matches the given format.
 *
 * Parameters:
 * - folder - the path to the folder to search in				| ex: "../data/"
 * - format - the file extension to filter by (without the dot) | ex: ".mtx"
 * 
 * Returns:
 * - Vector<String> - contains full paths to all matching files | ex: {"../ data/add20.mtx", "../data/add32.mtx"}
 */
Vector<String> GetFileNames(const String& folder, const String& format);

/*
 * Generates a random permutation of integers in the range [0, n - 1].
 *
 * This function creates a sequence of integers from 0 to n - 1
 * and shuffles it using a random number generator based on std::mt19937.
 * 
 * Parameters:
 * - n - the size of the permutation				 | ex: 5
 * 
 * Returns:
 * - Vector<int_t> - contains the shuffled sequence  | ex: {4, 2, 3, 0, 1}
 */
Vector<int_t> GetRandomPermutation(int_t n);