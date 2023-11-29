//
// Created by piotr on 28.11.2023.
//

#include "headers/Files.h"

Files::Files() {
    this->save_path = std::filesystem::current_path() / "pass.json";
}

std::vector<SinglePassword> Files::GetPasswordsFromFile() {
    std::ifstream file_data(this->save_path);
    if(file_data.good()){
        try{
            std::vector<SinglePassword> passwords;
            json _json = json::parse(file_data);
            for(json inner : _json["passwords"]){
                Encrypt encrypt;
                encrypt.SetEncrypted(inner.value("password", ""));
                SinglePassword pass = {
                    .id = inner.value("id", 0),
                    .name = inner.value("name", ""),
                    .username = inner.value("username", ""),
                    .url = inner.value("url", ""),
                    .password = encrypt,
                };
                passwords.push_back(pass);
            }
            return passwords;
        } catch (json::parse_error& exception){
            printf("[JSON ERR] %zu\n", exception.byte);
        }
    }

    return {};
}
