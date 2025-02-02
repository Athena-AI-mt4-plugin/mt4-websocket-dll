#include "encryption.h"
#include <openssl/aes.h>
#include <iostream>

const unsigned char key[32] = "mysecretkey1234567890123456789012"; // 32-byte key for AES-256

std::string AES_Encrypt(const std::string& plaintext) {
    AES_KEY encryptKey;
    AES_set_encrypt_key(key, 256, &encryptKey);
    
    unsigned char encrypted[128];
    AES_encrypt(reinterpret_cast<const unsigned char*>(plaintext.c_str()), encrypted, &encryptKey);
    
    return std::string(reinterpret_cast<char*>(encrypted), plaintext.length());
}

std::string AES_Decrypt(const std::string& ciphertext) {
    AES_KEY decryptKey;
    AES_set_decrypt_key(key, 256, &decryptKey);

    unsigned char decrypted[128];
    AES_decrypt(reinterpret_cast<const unsigned char*>(ciphertext.c_str()), decrypted, &decryptKey);
    
    return std::string(reinterpret_cast<char*>(decrypted), ciphertext.length());
}
