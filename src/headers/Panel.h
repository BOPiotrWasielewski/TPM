//
// Created by piotr on 26.11.2023.
//

#ifndef TPM_PANEL_H
#define TPM_PANEL_H

#include <cstdlib>
#include <cstdio>
#include <string>
#include <windows.h>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include "PasswordManager.h"
#include "Files.h"

using namespace ftxui;
class Panel {
private:
    char* title;
    PasswordManager manager;
    Files filesystem;

    SinglePassword selected_passwd;

    Component render(const std::function<void(SinglePassword)> &update_current_passwd);
    std::shared_ptr<ComponentBase> GetPasswordList(const std::function<void(SinglePassword)> &update_current_passwd);
    std::shared_ptr<ComponentBase> GetDetailsView();
public:
    explicit Panel(char* title);
    void draw();
};


#endif //TPM_PANEL_H
