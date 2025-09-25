#include "utils.hpp"

std::vector<std::string> getFileNames(const std::string& folder, const std::string& format) {
    std::vector<std::string> file_names(0);

    for (const auto& entry : std::filesystem::directory_iterator(folder)) {
        if (entry.is_regular_file() && entry.path().extension() == "." + format) {
            file_names.push_back(entry.path().string());
        }
    }

    return file_names;
}