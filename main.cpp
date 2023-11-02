#include <iostream>
#include "aes_encryption.h"
#include "aes_decryption.h"
#include "file_working.h"
#include "random_key.h"
#include <iostream>

int main() {
    std::string plaintext;
    std::cout << "Введите текст для шифрования : " << std::endl;
    std::cin >> plaintext;
    
    std::string key = generateRandomKey(32);

    std::string encryptedText = encryptAES(plaintext, key);
    writeToFile("encrypted.txt", encryptedText);

    std::string decryptedText = decryptAES(encryptedText, key);
    writeToFile("decrypted.txt", decryptedText);

    std::string importedEncryptedText = readFromFile("encrypted.txt");
    std::cout << "Зашифрованный текст из файла: " << importedEncryptedText << std::endl;

    std::string importedDecryptedText = readFromFile("decrypted.txt");
    std::cout << "Расшифрованный текст из файла: " << importedDecryptedText << std::endl;

    return 0;
}