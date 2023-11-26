//
// Created by piotr on 26.11.2023.
//

#ifndef TPM_PANEL_H
#define TPM_PANEL_H

#include <cstdlib>
#include <cstdio>
#include <string>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include "Passwords.h"

#if _WIN32 || _WIN64
    #include <windows.h>
#endif

using namespace ftxui;
class Panel {
private:
    char* title;
    Passwords passwords;
public:
    explicit Panel(char* title);
    void render();
};


#endif //TPM_PANEL_H
