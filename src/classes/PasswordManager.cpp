//
// Created by piotr on 26.11.2023.
//

#include <ftxui/dom/table.hpp>
#include "headers/PasswordManager.h"

PasswordManager::PasswordManager() = default;

void PasswordManager::Add(SinglePassword object) {
    this->passwords.push_back(object);
}

SinglePassword PasswordManager::Get(int i) {
    return !this->passwords.empty() ? this->passwords[i] : SinglePassword();
}

bool PasswordManager::IsEmpty() {
    return this->passwords.empty();
}

std::shared_ptr<ftxui::ComponentBase> PasswordManager::GetListComponent(int i, const std::function<void(std::string)>& test) {
    if(this->IsEmpty()) return {};

    SinglePassword pass = this->passwords[i];

    auto open = ftxui::Button("Więcej", [=]{test(pass.name);}, ftxui::ButtonOption::Ascii());
    return ftxui::Renderer(open, [=]{
        return ftxui::hbox({
           ftxui::text(pass.name) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 18),
           ftxui::text(pass.username) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20),
           ftxui::text("***********") | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20),
           ftxui::text(pass.url) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20),
           open->Render()
       });
    });
}

std::shared_ptr<ftxui::ComponentBase> PasswordManager::GetPasswordList(const std::function<void(std::string)>& test) {
    auto container = ftxui::Container::Vertical({});

    if(!this->IsEmpty()){
        for(int i = 0; i < this->passwords.size(); i++){
            auto component = this->GetListComponent(i, test);
            container->Add(ftxui::Renderer(component, [=]{
                return ftxui::hbox(component->Render());
            }));
        }
    }

    container = ftxui::Renderer(container, [=]{
        return ftxui::vbox({
            ftxui::hbox({{
                ftxui::bold(ftxui::text("Nazwa")) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 18),
                ftxui::bold(ftxui::text("Użytkownik")) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20),
                ftxui::bold(ftxui::text("Hasło")) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20),
                ftxui::bold(ftxui::text("Link")) | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20)
            }
        }), ftxui::separator(), ftxui::vbox({container->Render()}) | ftxui::vscroll_indicator | ftxui::yframe});
    });

    return container;
}
