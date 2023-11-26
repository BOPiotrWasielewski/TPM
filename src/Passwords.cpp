//
// Created by piotr on 26.11.2023.
//

#include "Passwords.h"

Passwords::Passwords() = default;

void Passwords::Add(SinglePassword object) {
    this->passwords.push_back(object);
}

std::vector<SinglePassword> Passwords::GetAll() {
    return this->passwords;
}

SinglePassword Passwords::Get(int i) {
    return !this->passwords.empty() ? this->passwords[i] : SinglePassword();
}

bool Passwords::IsEmpty() {
    return this->passwords.empty();
}
