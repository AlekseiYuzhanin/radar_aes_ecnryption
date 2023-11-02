#include "aes_decryption.h"
#include <openssl/evp.h>
#include <cstring>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <iostream>

std::string decryptAES(const std::string& encryptedText, const std::string& key) {
    const EVP_CIPHER* cipher = EVP_get_cipherbyname("aes-256-cbc");
    if (!cipher) {
        std::cerr << "Ошибка получения алгоритма шифрования" << std::endl;
        return "";
    }

    unsigned char iv[EVP_MAX_IV_LENGTH];
    memset(iv, 0x00, EVP_MAX_IV_LENGTH);

    EVP_CIPHER_CTX* ctx;
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        std::cerr << "Ошибка создания контекста шифрования" << std::endl;
        return "";
    }

    if (EVP_DecryptInit_ex(ctx, cipher, NULL, reinterpret_cast<const unsigned char*>(key.c_str()), iv) != 1) {
        std::cerr << "Ошибка инициализации дешифрования" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }

    BIO* bio = BIO_new_mem_buf(encryptedText.c_str(), -1);
    BIO* base64 = BIO_new(BIO_f_base64());
    BIO_push(base64, bio);

    int decryptedLength = BIO_pending(base64);
    unsigned char* decryptedText = new unsigned char[decryptedLength];
    decryptedLength = BIO_read(base64, decryptedText, decryptedLength);

    int plaintextLength;
    if (EVP_DecryptUpdate(ctx, decryptedText, &plaintextLength, decryptedText, decryptedLength) != 1) {
        std::cerr << "Ошибка дешифрования" << std::endl;
        delete[] decryptedText;
        EVP_CIPHER_CTX_free(ctx);
        BIO_free_all(base64);
        return "";
    }

    int finalPlaintextLength;
    if (EVP_DecryptFinal_ex(ctx, decryptedText + plaintextLength, &finalPlaintextLength) != 1) {
        std::cerr << "Ошибка завершения дешифрования" << std::endl;
        delete[] decryptedText;
        EVP_CIPHER_CTX_free(ctx);
        BIO_free_all(base64);
        return "";
    }

    std::string decryptedTextStr(reinterpret_cast<char*>(decryptedText), plaintextLength + finalPlaintextLength);

    delete[] decryptedText;
    EVP_CIPHER_CTX_free(ctx);
    BIO_free_all(base64);

    return decryptedTextStr;
}
