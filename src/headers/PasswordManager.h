//
// Created by piotr on 26.11.2023.
//

#ifndef TPM_PASSWORDMANAGER_H
#define TPM_PASSWORDMANAGER_H

#include <vector>
#include <string>
#include <ftxui/component/component.hpp>
#include "Encrypt.h"

struct SinglePassword {
    int id{};
    std::string name{};
    std::string username{};
    std::string url{};
    std::string password;
};

#endif //TPM_PASSWORDMANAGER_H
