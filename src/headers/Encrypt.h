//
// Created by piotr on 29.11.2023.
//

#ifndef TPM_ENCRYPT_H
#define TPM_ENCRYPT_H

#include <string>

class Encrypt {
private:
    std::string original;
    std::string encrypted;
    std::string crypto_key;
    std::string EncryptPassword(const std::string& value);
public:
    Encrypt(std::string crypto_key = "5JMMLlOpjZ");
    void SetOriginal(const std::string& original);
    void SetEncrypted(const std::string& encrypted);
    std::string GetOriginal();
    std::string GetEncrypted();
};


#endif //TPM_ENCRYPT_H
