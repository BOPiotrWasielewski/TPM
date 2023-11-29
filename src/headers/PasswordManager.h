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
    Encrypt password;
};

class PasswordManager {
private:
    std::vector<SinglePassword> passwords;
public:
    PasswordManager();
    void Add(SinglePassword object);
    SinglePassword Get(int cid);
    bool IsEmpty();
    int size();
    std::shared_ptr<ftxui::ComponentBase> GetListComponent(int i, const std::function<void(SinglePassword)> &update_current_passwd);
};

#endif //TPM_PASSWORDMANAGER_H
