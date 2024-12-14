#include "PasswordEncryption.h"
#include <random>
#include <sstream>
#include <iomanip>

/**
 * Generates a random salt of fixed length.
 */
std::string generateSalt(size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(charset) - 2);

    std::string salt;
    for (size_t i = 0; i < length; ++i) {
        salt += charset[dis(gen)];
    }
    return salt;
}

/**
 * Simple substitution-based encryption algorithm.
 */
std::string simpleEncrypt(const std::string& input, const std::string& salt) {
    std::string encrypted;
    for (size_t i = 0; i < input.size(); ++i) {
        char encryptedChar = input[i] + salt[i % salt.size()];
        encrypted += encryptedChar;
    }
    return encrypted;
}

std::string PasswordEncryptor::encryptPassword(const std::string& password) {
    const size_t saltLength = 8;
    std::string salt = generateSalt(saltLength);

    std::string encryptedPassword = simpleEncrypt(password, salt);

    // Append salt to encrypted password
    return encryptedPassword + salt;
}
std::string PasswordEncryptor::verifyPassword(const std::string& password, const std::string& encryptedData) {

    bool isVerified = (password == encryptedData);

    if (isVerified) {
        return "Password is correct";
    }
    else {
        return "Password is incorrect";
    }
}
