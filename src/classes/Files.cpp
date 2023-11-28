//
// Created by piotr on 28.11.2023.
//

#include "headers/Files.h"

Files::Files() {
    this->save_path = std::filesystem::current_path() / "pass.json";
}
