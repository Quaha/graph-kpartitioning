#include "utils.hpp"

Vector<String> getFileNames(const String& folder, const String& format) {
    Vector<String> file_names;

    for (const auto& entry : std::filesystem::directory_iterator(folder)) {
        if (entry.is_regular_file() && entry.path().extension() == "." + format) {
            file_names.push_back(entry.path().string());
        }
    }

    return file_names;
}