#include "file_working.h"
#include <string>
#include <fstream>
#include <iostream>

void writeToFile(const std::string& filename, const std::string& text) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << text;
        file.close();
        std::cout << "Данные успешно записаны в файл: " << filename << std::endl;
    } else {
        std::cerr << "Ошибка открытия файла для записи: " << filename << std::endl;
    }
}

std::string readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string data;
        std::getline(file, data);
        file.close();
        return data;
    } else {
        std::cerr << "Ошибка открытия файла для чтения: " << filename << std::endl;
        return "";
    }
}
