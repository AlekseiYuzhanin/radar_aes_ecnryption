#include "random_key.h"
#include <string>
#include <iostream>
#include <openssl/rand.h>

std::string generateRandomKey(int keyLength) {
    std::string key;
    key.resize(keyLength);

    if (RAND_bytes(reinterpret_cast<unsigned char*>(&key[0]), keyLength) != 1) {
        std::cerr << "Ошибка генерации ключа" << std::endl;
        return "";
    }

    return key;
}
