//
// Created by piotr on 26.11.2023.
//

#ifndef TPM_PASSWORDS_H
#define TPM_PASSWORDS_H

#include <vector>

struct SinglePassword {
    char* name;
    char* url;
    char* password;
};

class Passwords {
private:
    std::vector<SinglePassword> passwords;
public:
    Passwords();
    void Add(SinglePassword object);
    std::vector<SinglePassword> GetAll();
    SinglePassword Get(int i);
    bool IsEmpty();
};

#endif //TPM_PASSWORDS_H
