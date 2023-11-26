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
    this->passwords = Passwords();
}

void Panel::render() {
    ScreenInteractive _screen = ScreenInteractive::Fullscreen();

    this->passwords.Add({.id =  1, .name =  "name 1", .username =  "test 123", .url =  "https://google.com", .password =  "abc123"});
    this->passwords.Add({.id =  2, .name =  "name 2", .username =  "test 123", .url =  "https://google.com", .password =  "abc123"});
    this->passwords.Add({.id =  3, .name =  "name 3", .username =  "test 123", .url =  "https://google.com", .password =  "abc123"});
    this->passwords.Add({.id =  4, .name =  "name 4", .username =  "test 123", .url =  "https://google.com", .password =  "abc123"});

    std::string t = "abc";

    auto passComponent = passwords.GetSelectRender([&](std::string test){
        t = test;
    });
    auto doc = Renderer(passComponent, [&]{
        return gridbox({
           {window(text("Win 1"), passComponent->Render()) | flex, window(text("Win 2"), text(t)) | size(WIDTH, GREATER_THAN, 40)}
        });
    });

    _screen.Loop(doc);
}
