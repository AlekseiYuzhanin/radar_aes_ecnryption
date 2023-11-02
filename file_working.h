#ifndef FILE_WORKING_H
#define FILE_WORKING_H

#include <string>

void writeToFile(const std::string& filename, const std::string& text);
std::string readFromFile(const std::string& filename);

#endif