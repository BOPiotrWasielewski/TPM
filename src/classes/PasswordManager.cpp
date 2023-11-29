//
// Created by piotr on 26.11.2023.
//

#include <ftxui/dom/table.hpp>
#include "headers/PasswordManager.h"

PasswordManager::PasswordManager() = default;

void PasswordManager::Add(SinglePassword object) {
    this->passwords.push_back(object);
}

SinglePassword PasswordManager::Get(int cid) {
    if(this->passwords.empty()){
        for(SinglePassword pass : this->passwords){
            if(pass.id == cid) return pass;
        }
    }
    return {};
}

bool PasswordManager::IsEmpty() {
    return this->passwords.empty();
}

int PasswordManager::size() {
    return this->passwords.size();
}

std::shared_ptr<ftxui::ComponentBase> PasswordManager::GetListComponent(int i, const std::function<void(SinglePassword)> &update_current_passwd) {
    if(this->IsEmpty()) return {};

    SinglePassword pass = this->passwords[i];

    auto open = ftxui::Button("Więcej", [=]{update_current_passwd(pass);}, ftxui::ButtonOption::Ascii());
    return ftxui::Renderer(open, [=]{
        return ftxui::hbox({
           ftxui::text(pass.name) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 18),
           ftxui::text(pass.username) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20),
           ftxui::text("***********") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 18),
           ftxui::text(pass.url) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20),
           open->Render()
       });
    });
}
