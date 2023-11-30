//
// Created by piotr on 28.11.2023.
//

#ifndef TPM_FILES_H
#define TPM_FILES_H

#include <cstdio>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <codecvt>
#include <nlohmann/json.hpp>
#include "PasswordManager.h"

using json = nlohmann::json;
class Files {
private:
    std::filesystem::path save_path;
public:
    Files();
    std::vector<SinglePassword> GetPasswordsFromFile();
};


#endif //TPM_FILES_H
