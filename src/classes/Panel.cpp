//
// Created by piotr on 26.11.2023.
//

#include "headers/Panel.h"

Panel::Panel(std::string title) {
    const char* _title = title.c_str();

    SetConsoleTitle(_title);
    system("chcp 65001");
    system("cls");

    this->filesystem = Files();
}

void Panel::draw() {
    this->manager = this->filesystem.GetPasswordsFromFile();

    ScreenInteractive _screen = ScreenInteractive::Fullscreen();

    auto update_current_details = [&](SinglePassword passwd){
        this->selected_passwd = std::move(passwd);
        _screen.PostEvent(Event::Custom);
    };
    auto add_new_password = [&]{
        if(!this->pass_to_add.name.empty() && !this->pass_to_add.password.empty()){
            Encrypt enc;
            enc.SetOriginal(this->pass_to_add.password);
            this->pass_to_add.password = enc.GetEncrypted();
            this->manager.push_back(this->pass_to_add);
            this->pass_to_add.name = ""; this->pass_to_add.username = ""; this->pass_to_add.url = ""; this->pass_to_add.password = "";
            this->show_add_modal = false;
            this->regenerate_pass_list(update_current_details);
            _screen.PostEvent(Event::Custom);
        }
    };

    this->regenerate_pass_list(update_current_details);

    auto component = this->render(update_current_details, add_new_password);
    auto document = Renderer(component, [&]{
        return vbox({component->Render()});
    });
//    std::thread update([&]() {
//        for (;;) {
//            using namespace std::chrono_literals;
//            std::this_thread::sleep_for(0.05s);
//            bool test = this->regenerate_pass_list(update_current_details);
//            if(test){
//                shift++;
//                _screen.PostEvent(Event::Custom);
//            }
//        }
//    });

    _screen.Loop(document);
}

Component Panel::render(const std::function<void(SinglePassword)> &update_current_details, const std::function<void()> &add_new_password) {
    auto passComponent = this->GetPasswordListView(update_current_details);
    auto details = this->GetDetailsView();
    auto controls = this->GetControlView();

    auto doc = Container::Horizontal({passComponent, details, controls});
    doc = Renderer(doc, [=]{
        return gridbox({
            {window(text(" Lista haseł "), passComponent->Render()) | flex, window(text(" Szczegóły "), details->Render()) | size(WIDTH, GREATER_THAN, 45)},
            {window(text(" Sterowanie "), controls->Render())},
        });
    });

    auto hide_modal = [&]{ this->show_add_modal = false; };
    auto add_new_modal = this->GetAddNewPasswordModal(hide_modal, add_new_password);
    doc |= Modal(add_new_modal, &this->show_add_modal);

    return doc;
}

std::shared_ptr<ComponentBase> Panel::GetDetailsView() {
    auto render = Container::Vertical({});

    // Prepare copy buttons
    auto copy_username = Button("kopiuj", [&, this]{
        this->clipboard << this->selected_passwd.username;
    }, ButtonOption::Ascii());
    auto copy_password = Button("kopiuj", [&, this]{
        Encrypt enc;
        enc.SetEncrypted(this->selected_passwd.password);
        this->clipboard << enc.GetOriginal();
    }, ButtonOption::Ascii());
    auto copy_url = Button("kopiuj", [&, this]{
        this->clipboard << this->selected_passwd.url;
    }, ButtonOption::Ascii());

    // Prepare fields to render
    render->Add(Renderer([=, this]{ return hbox({text("Shift: "+std::to_string(this->shift))}); }));
    render->Add(Renderer([=, this]{ return hbox({text("ID: "+std::to_string(this->selected_passwd.id))}); }));
    render->Add(Renderer([=, this]{ return hbox({text("Nazwa: "+this->selected_passwd.name)}); }));
    render->Add(Renderer(copy_username, [=, this]{ return hbox({text("Użytkownik: "+this->selected_passwd.username), text(" | "), copy_username->Render()}); }));
    render->Add(Renderer(copy_password, [=, this]{ return hbox({text("Hasło: "+this->selected_passwd.password), text(" | "), copy_password->Render()}); }));
    render->Add(Renderer(copy_url, [=, this]{ return hbox({text("Link: "+this->selected_passwd.url), text(" | "), copy_url->Render()}); }));

    render = Renderer(render, [=]{
        return render->Render();
    });
    return render;
}

std::shared_ptr<ComponentBase> Panel::GetControlView() {
    auto render = Container::Horizontal({});
    auto add_new_button = Button("Dodaj hasło", [&]{ this->show_add_modal = true; }, ButtonOption::Simple());
    auto remove_button = Button("Usuń hasło", [&]{}, ButtonOption::Simple());

    render->Add(add_new_button);
    render->Add(remove_button);

    render = Renderer(render, [=]{
        return hbox({
            add_new_button->Render() | flex,
            separator(),
            remove_button->Render() | flex
        }) | flex;
    });
    return render;
}

std::shared_ptr<ComponentBase> Panel::GetAddNewPasswordModal(const std::function<void()> &hide_modal, const std::function<void()> &add_new_password) {
    auto input_name = Input(&this->pass_to_add.name, "Panel logowania");
    auto input_user = Input(&this->pass_to_add.username, "admin");
    auto input_url = Input(&this->pass_to_add.url, "https://google.com/");
    auto input_pass = Input(&this->pass_to_add.password, {
        .placeholder = "********",
        .password = true,
    });
    auto btn_add = Button("Dodaj", add_new_password);
    auto btn_cancel = Button("Anuluj", hide_modal);

    auto render = Container::Vertical({
        input_name,
        input_user,
        input_url,
        input_pass,
        btn_add,
        btn_cancel
    });

    render = Renderer(render, [=]{
        return vbox({
            text("Dodawanie nowego hasła"),
            separator(),
            hbox({text("Nazwa*: "), input_name->Render()}),
            hbox({text("Użytkownik: "), input_user->Render()}),
            hbox({text("URL: "), input_url->Render()}),
            hbox({text("Hasło*: "), input_pass->Render()}),
            btn_add->Render(),
            btn_cancel->Render()
        }) | border | size(WIDTH, GREATER_THAN, 50);
    });

    return render;
}

std::shared_ptr<ComponentBase> Panel::GetPasswordListView(const std::function<void(SinglePassword)> &update_current_details) {
    auto container = Container::Vertical(this->passList);

    container = Renderer(container, [=]{
        return vbox({
            hbox({
                {
                    bold(text("Nazwa")) | size(WIDTH, EQUAL, 18),
                    bold(text("Użytkownik")) | size(WIDTH, EQUAL, 20),
                    bold(text("Hasło")) | size(WIDTH, EQUAL, 18),
                    bold(text("Link")) | size(WIDTH, EQUAL, 20)
                }
            }), separator(), vbox({container->Render()}) | vscroll_indicator | yframe | size(HEIGHT, LESS_THAN, 22)
        });
    });

    return container;
}

bool Panel::regenerate_pass_list(const std::function<void(SinglePassword)> &update_current_details) {
    if(!this->manager.empty()){
        this->passList.clear();
        for(SinglePassword pass : this->manager){
            this->passList.push_back(Panel::GetListComponent(pass, update_current_details));
        }
        return true;
    }
    return false;
}

std::shared_ptr<ftxui::ComponentBase>
Panel::GetListComponent(const SinglePassword& pass, const std::function<void(SinglePassword)> &update_current_details) {
    auto open = ftxui::Button("Więcej", [=]{update_current_details(pass);}, ftxui::ButtonOption::Ascii());
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