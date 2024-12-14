#include <string>

class __declspec(dllexport) PasswordEncryptor {
public:

    PasswordEncryptor() = default;


    std::string encryptPassword(const std::string& password);


    bool verifyPassword(const std::string& password, const std::string& encryptedData);
};
 