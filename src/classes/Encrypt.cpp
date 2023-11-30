//
// Created by piotr on 29.11.2023.
//

#include "headers/Encrypt.h"

Encrypt::Encrypt(std::string crypto_key) {
    this->crypto_key = std::move(crypto_key);
}

void Encrypt::SetOriginal(const std::string& o) {
    this->original = o;
    this->encrypted = base64::to_base64(this->original);
}

void Encrypt::SetEncrypted(const std::string& e) {
    this->encrypted = e;
    this->original = base64::from_base64(this->encrypted);
}

std::string Encrypt::GetOriginal() {
    return this->original;
}

std::string Encrypt::GetEncrypted() {
    return this->encrypted;
}
