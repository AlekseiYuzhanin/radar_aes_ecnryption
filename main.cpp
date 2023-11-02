#include <iostream>
#include "aes_encryption.h"
#include "aes_decryption.h"
#include <iostream>

int main() {
    std::string plaintext;
    std::string key;

    std::cout << "Введите текст для шифрования : " << std::endl;
    std::cin >> plaintext;
    std::cout << "Введите ключ для шифрования : " << std::endl;
    std::cin >> key;

    std::string encryptedText = encryptAES(plaintext, key);
    std::cout << "Зашифрованный текст: " << encryptedText << std::endl;

    std::string decryptedText = decryptAES(encryptedText, key);
    std::cout << "Расшифрованный текст: " << decryptedText << std::endl;

    return 0;
}