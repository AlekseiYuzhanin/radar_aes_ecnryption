#include "aes_encryption.h"
#include <openssl/evp.h>
#include <cstring>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <iostream>

std::string encryptAES(const std::string& plaintext, const std::string& key) {
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

    if (EVP_EncryptInit_ex(ctx, cipher, NULL, reinterpret_cast<const unsigned char*>(key.c_str()), iv) != 1) {
        std::cerr << "Ошибка инициализации шифрования" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }

    int plaintextLength = plaintext.length() + EVP_MAX_BLOCK_LENGTH;
    unsigned char* ciphertext = new unsigned char[plaintextLength];

    int ciphertextLength;
    if (EVP_EncryptUpdate(ctx, ciphertext, &ciphertextLength, reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length()) != 1) {
        std::cerr << "Ошибка шифрования" << std::endl;
        delete[] ciphertext;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }

    int finalCiphertextLength;
    if (EVP_EncryptFinal_ex(ctx, ciphertext + ciphertextLength, &finalCiphertextLength) != 1) {
        std::cerr << "Ошибка завершения шифрования" << std::endl;
        delete[] ciphertext;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }

    std::string encodedCiphertext;
    BIO* base64 = BIO_new(BIO_f_base64());
    BIO* bio = BIO_new(BIO_s_mem());
    BIO_set_flags(base64, BIO_FLAGS_BASE64_NO_NL);
    BIO_push(base64, bio);
    BIO_write(base64, ciphertext, ciphertextLength + finalCiphertextLength);
    BIO_flush(base64);

    BUF_MEM* bufferPtr;
    BIO_get_mem_ptr(base64, &bufferPtr);
    encodedCiphertext.assign(bufferPtr->data, bufferPtr->length - 1);

    delete[] ciphertext;
    EVP_CIPHER_CTX_free(ctx);
    BIO_free_all(base64);

    return encodedCiphertext;
}