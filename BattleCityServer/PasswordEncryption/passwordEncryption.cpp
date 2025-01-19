#include "PasswordEncryption.h"
#include <regex>
#include <string>

std::string PasswordEncryptor::regexEncrypt(const std::string& input) {
    std::string encrypted = input;

    encrypted = std::regex_replace(encrypted, std::regex("a"), "1");
    encrypted = std::regex_replace(encrypted, std::regex("e"), "2");
    encrypted = std::regex_replace(encrypted, std::regex("i"), "3");
    encrypted = std::regex_replace(encrypted, std::regex("o"), "4");
    encrypted = std::regex_replace(encrypted, std::regex("u"), "5");

    return encrypted;
}

std::string PasswordEncryptor::regexDecrypt(const std::string& encrypted) {
    std::string decrypted = encrypted;

    decrypted = std::regex_replace(decrypted, std::regex("1"), "a");
    decrypted = std::regex_replace(decrypted, std::regex("2"), "e");
    decrypted = std::regex_replace(decrypted, std::regex("3"), "i");
    decrypted = std::regex_replace(decrypted, std::regex("4"), "o");
    decrypted = std::regex_replace(decrypted, std::regex("5"), "u");

    return decrypted;
}

std::string PasswordEncryptor::encryptPassword(const std::string& password) {
    return regexEncrypt(password);
}
bool PasswordEncryptor::verifyPassword(const std::string& password, const std::string& encryptedData) {

    std::string decryptedPassword = regexDecrypt(encryptedData);
    return decryptedPassword == password;
}
