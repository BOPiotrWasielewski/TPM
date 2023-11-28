//
// Created by piotr on 26.11.2023.
//

#include "headers/Panel.h"

Panel::Panel(char *title) {
    this->title = title;

    SetConsoleTitle(this->title);
    system("chcp 65001");
    system("cls");

    this->manager = PasswordManager();
    this->filesystem = Files();
}

void Panel::render() {
    ScreenInteractive _screen = ScreenInteractive::Fullscreen();

    this->manager.Add({.id =  1, .name =  "name 1", .username =  "test 123", .url =  "https://google.com", .password =  "abc123"});

    std::string t = "abc";

    auto passComponent = this->manager.GetPasswordList([&](std::string test){
        t = test;
        _screen.PostEvent(Event::Custom);
    });
    auto doc = Renderer(passComponent, [&]{
        return gridbox({
           {window(text(" Lista haseł "), passComponent->Render()) | flex, window(text(" Szczegóły "), text(t)) | size(WIDTH, GREATER_THAN, 40)}
        });
    });

    _screen.Loop(doc);
}
