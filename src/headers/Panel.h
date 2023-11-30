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
#include <clipboardxx.hpp>
#include "PasswordManager.h"
#include "Files.h"

using namespace ftxui;
class Panel {
private:
    int shift = 0;
    std::vector<SinglePassword> manager;
    std::vector<Component> passList;
    Files filesystem;

    SinglePassword selected_passwd;
    clipboardxx::clipboard clipboard;
    bool show_add_modal = false;

    SinglePassword pass_to_add;

    Component render(const std::function<void(SinglePassword)> &update_current_details, const std::function<void()> &add_new_password);
    std::shared_ptr<ComponentBase> GetPasswordListView(const std::function<void(SinglePassword)> &update_current_details);
    std::shared_ptr<ComponentBase> GetDetailsView();
    std::shared_ptr<ComponentBase> GetControlView();
    std::shared_ptr<ComponentBase> GetAddNewPasswordModal(const std::function<void()> &hide_modal, const std::function<void()> &add_new_password);
    bool regenerate_pass_list(const std::function<void(SinglePassword)> &update_current_details);
    static std::shared_ptr<ftxui::ComponentBase> GetListComponent(const SinglePassword &pass, const std::function<void(SinglePassword)> &update_current_details);
public:
    explicit Panel(std::string title);
    void draw();
};


#endif //TPM_PANEL_H
