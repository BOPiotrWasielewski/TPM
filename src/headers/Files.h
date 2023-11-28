//
// Created by piotr on 28.11.2023.
//

#ifndef TPM_FILES_H
#define TPM_FILES_H

#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
class Files {
private:
    std::filesystem::path save_path;
public:
    Files();
};


#endif //TPM_FILES_H
