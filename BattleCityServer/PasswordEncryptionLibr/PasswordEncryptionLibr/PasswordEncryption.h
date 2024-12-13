#ifndef PASSWORD_ENCRYPTOR_H
#define PASSWORD_ENCRYPTOR_H

#include <string>

class PasswordEncryptor {
public:
    /**
     * Encrypts a password using a basic custom encryption algorithm combined with a randomly generated salt.
     * @param password The password string to encrypt.
     * @return The encrypted password combined with the salt.
     */
    static std::string encryptPassword(const std::string& password);

    /**
     * Verifies if the input password matches the encrypted string.
     * @param password The password string to verify.
     * @param encryptedData The encrypted password combined with the salt.
     * @return True if the password matches, false otherwise.
     */
    static bool verifyPassword(const std::string& password, const std::string& encryptedData);
};

#endif // PASSWORD_ENCRYPTOR_H
