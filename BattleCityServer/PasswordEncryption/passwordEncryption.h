#include <string>

class PasswordEncryptor {
public:

    PasswordEncryptor() = default;


    std::string encryptPassword(const std::string& password);


    std::string verifyPassword(const std::string& password, const std::string& encryptedData);
};
 