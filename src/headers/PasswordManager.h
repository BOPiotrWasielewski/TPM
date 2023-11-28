//
// Created by piotr on 26.11.2023.
//

#ifndef TPM_PASSWORDMANAGER_H
#define TPM_PASSWORDMANAGER_H

#include <vector>
#include <string>
#include <ftxui/component/component.hpp>

struct SinglePassword {
    int id{};
    std::string name{};
    std::string username{};
    std::string url{};
    std::string password{};
};

class PasswordManager {
private:
    std::vector<SinglePassword> passwords;
    std::shared_ptr<ftxui::ComponentBase> GetListComponent(int i, const std::function<void(std::string)>& test);
public:
    PasswordManager();
    void Add(SinglePassword object);
    SinglePassword Get(int i);
    bool IsEmpty();
    std::shared_ptr<ftxui::ComponentBase> GetPasswordList(const std::function<void(std::string)>& test);
};

#endif //TPM_PASSWORDMANAGER_H
