//
// Created by piotr on 26.11.2023.
//

#include "Panel.h"

Panel::Panel(char *title) {
    this->title = title;

    SetConsoleTitle(this->title);
    system("chcp 65001");
    this->clear();
}

void Panel::clear() {
    system("cls");
}

void Panel::render() {
    Passwords passwords = Passwords();
    passwords.Add({"name 1", "https://google.com", "abc123"});
    passwords.Add({"name 2", "https://google.com", "cba321"});
    passwords.Add({"name 3", "https://google.com", "123abc"});
    passwords.Add({"name 4", "https://google.com", "123cba"});
    ScreenInteractive _screen = ScreenInteractive::TerminalOutput();

    auto winContent = Container::Vertical({
        Button("Test 1", []{}),
        Button("Test 2", []{}),
        Button("Test 3", []{}),
    });
    auto doc = Renderer(winContent, [&]{
        return gridbox({
           {window(text("Win 1"), winContent->Render()) | flex, window(text("Win 2"), text("abc")) | flex}
        });
    });

    _screen.Loop(doc);
}
