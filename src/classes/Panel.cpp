//
// Created by piotr on 26.11.2023.
//

#include <utility>

#include "headers/Panel.h"

Panel::Panel(char *title) {
    this->title = title;

    SetConsoleTitle(this->title);
    system("chcp 65001");
    system("cls");

    this->manager = PasswordManager();
    this->filesystem = Files();
}

std::shared_ptr<ComponentBase> Panel::GetPasswordList(const std::function<void(SinglePassword)> &update_current_passwd) {
    auto container = Container::Vertical({});

    if(!this->manager.IsEmpty()){
        for(int i = 0; i < this->manager.size(); i++){
            auto component = this->manager.GetListComponent(i, update_current_passwd);
            container->Add(Renderer(component, [=]{
                return hbox(component->Render());
            }));
        }
    }

    container = Renderer(container, [=]{
        return vbox({
           hbox({
               {
                    bold(text("Nazwa")) | size(WIDTH, EQUAL, 18),
                    bold(text("Użytkownik")) | size(WIDTH, EQUAL, 20),
                    bold(text("Hasło")) | size(WIDTH, EQUAL, 18),
                    bold(text("Link")) | size(WIDTH, EQUAL, 20)
                }
           }), separator(), vbox({container->Render()}) | vscroll_indicator | yframe
        });
    });

    return container;
}

std::shared_ptr<ComponentBase> Panel::GetDetailsView() {
    auto render = Container::Vertical({});
    render->Add(Renderer([=, this]{ return vbox({text("ID: "+std::to_string(this->selected_passwd.id))}); }));
    render->Add(Renderer([=, this]{ return vbox({text("Nazwa: "+this->selected_passwd.name)}); }));
    render->Add(Renderer([=, this]{ return vbox({text("Użytkownik: "+this->selected_passwd.username)}); }));
    render->Add(Renderer([=, this]{ return vbox({text("Hasło: "+this->selected_passwd.password.GetEncrypted())}); }));
    render->Add(Renderer([=, this]{ return vbox({text("Link: "+this->selected_passwd.url)}); }));
    render = Renderer(render, [=]{
        return render->Render();
    });
    return render;
}

Component Panel::render(const std::function<void(SinglePassword)> &update_current_passwd) {
    auto passComponent = this->GetPasswordList(update_current_passwd);
    auto details = this->GetDetailsView();

    auto doc = Container::Horizontal({passComponent, details});
    doc = Renderer(doc, [=]{
        return gridbox({
            {window(text(" Lista haseł "), passComponent->Render()) | flex, window(text(" Szczegóły "), details->Render()) | size(WIDTH, GREATER_THAN, 45)}
        });
    });

    return doc;
}

void Panel::draw() {
    std::vector<SinglePassword> passwords = this->filesystem.GetPasswordsFromFile();
    if(!passwords.empty()){
        for(const SinglePassword& pass : passwords){
            this->manager.Add(pass);
        }
    }

    ScreenInteractive _screen = ScreenInteractive::Fullscreen();

    auto update_current_passwd = [&](SinglePassword passwd){
        this->selected_passwd = std::move(passwd);
        _screen.PostEvent(Event::Custom);
    };

    auto component = this->render(update_current_passwd);
    auto document = Renderer(component, [&]{
        return vbox({component->Render()});
    });
    _screen.Loop(document);
}
