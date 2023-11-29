//
// Created by piotr on 29.11.2023.
//

#include "headers/Encrypt.h"

Encrypt::Encrypt(std::string crypto_key) {
    this->crypto_key = std::move(crypto_key);
}

void Encrypt::SetOriginal(const std::string& o) {
    this->original = o;
    this->encrypted = this->EncryptPassword(this->original);
}

void Encrypt::SetEncrypted(const std::string& e) {
    this->encrypted = e;
    this->original = this->EncryptPassword(this->encrypted);
}

std::string Encrypt::GetOriginal() {
    return this->original;
}

std::string Encrypt::GetEncrypted() {
    return this->encrypted;
}

std::string Encrypt::EncryptPassword(const std::string& value) {
    std::string output = value;
    for(int i = 0; i < value.size(); i++){
        output[i] = value[i] ^ this->crypto_key[i % this->crypto_key.size()];
    }

    return output;
}
