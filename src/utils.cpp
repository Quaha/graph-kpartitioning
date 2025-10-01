#include "utils.hpp"

Vector<String> getFileNames(const String& folder, const String& format) {

    size_t sz = 0;

    for (const auto& entry : std::filesystem::directory_iterator(folder)) {
        if (entry.is_regular_file() && entry.path().extension() == "." + format) {
            sz++;
        }
    }

    Vector<String> file_names(sz);
    size_t p = 0;

    for (const auto& entry : std::filesystem::directory_iterator(folder)) {
        if (entry.is_regular_file() && entry.path().extension() == "." + format) {
            file_names[p++] = entry.path().string();
        }
    }

    return file_names;
}

Vector<int_t> getRandomPermutation(int_t n) {
    Vector<int_t> permutation(n);
    std::iota(permutation.begin(), permutation.end(), 0);

    std::random_device rd;
    std::mt19937 rng(rd());

    std::shuffle(permutation.begin(), permutation.end(), rng);

    return permutation;
}