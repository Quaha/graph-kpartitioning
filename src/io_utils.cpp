#include "io_utils.hpp"

std::vector<std::string> getMtxFileNames(const std::string& folder) {
    std::vector<std::string> file_names(0);

    for (const auto& entry : std::filesystem::directory_iterator(folder)) {
        if (entry.is_regular_file() && entry.path().extension() == ".mtx") {
            file_names.push_back(entry.path().string());
        }
    }

    return file_names;
}