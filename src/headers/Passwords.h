//
// Created by piotr on 26.11.2023.
//

#ifndef TPM_PASSWORDS_H
#define TPM_PASSWORDS_H

#include <vector>
#include <string>
#include <ftxui/component/component.hpp>

struct SinglePassword {
    int id;
    char* name;
    char* username;
    char* url = "#";
    char* password;
};

class Passwords {
private:
    std::vector<SinglePassword> passwords;
    std::vector<ftxui::Component> GenerateSelectComponents(const std::function<void(std::string)>& test);
public:
    Passwords();
    void Add(SinglePassword object);
    SinglePassword Get(int i);
    bool IsEmpty();
    std::shared_ptr<ftxui::ComponentBase> GetSelectRender(const std::function<void(std::string)>& test);
};

#endif //TPM_PASSWORDS_H
