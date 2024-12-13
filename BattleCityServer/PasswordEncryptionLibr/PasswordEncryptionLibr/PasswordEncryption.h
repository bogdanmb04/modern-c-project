#ifndef PASSWORDBYENCRYPTOR_H
#define PASSWORDBYENCRYPTOR_H

#include <string>

class PasswordEncryptor {
public:
    
    PasswordEncryptor() = default;

   
    std::string encryptPassword(const std::string& password);

    
    std::string verifyPassword(const std::string& password, const std::string& encryptedData);
};

#endif 