//
// Created by piotr on 26.11.2023.
//

#include "headers/Passwords.h"

Passwords::Passwords() = default;

void Passwords::Add(SinglePassword object) {
    this->passwords.push_back(object);
}

SinglePassword Passwords::Get(int i) {
    return !this->passwords.empty() ? this->passwords[i] : SinglePassword();
}

bool Passwords::IsEmpty() {
    return this->passwords.empty();
}

std::vector<ftxui::Component> Passwords::GenerateSelectComponents(const std::function<void(std::string)>& test) {
    if(this->IsEmpty()) return {};

    std::vector<ftxui::Component> components;
    for(SinglePassword pass : this->passwords){
        components.push_back(ftxui::Button(pass.name, [=]{test(pass.name);}));
    }

    return components;
}

std::shared_ptr<ftxui::ComponentBase> Passwords::GetSelectRender(const std::function<void(std::string)>& test) {
    auto buttons = this->GenerateSelectComponents(test);
    auto container = ftxui::Container::Vertical(buttons);

    container = ftxui::Renderer(container, [=]{
        return ftxui::hbox({container->Render() | ftxui::flex});
    });

    return container;
}
