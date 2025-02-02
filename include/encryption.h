#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

std::string AES_Encrypt(const std::string& plaintext);
std::string AES_Decrypt(const std::string& ciphertext);

#endif // ENCRYPTION_H
