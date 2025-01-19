#include <string>
#include <regex>

class __declspec(dllexport) PasswordEncryptor {
public:
    PasswordEncryptor() = default;

    std::string encryptPassword(const std::string& password);
    bool verifyPassword(const std::string& password, const std::string& encryptedData);

private:
    std::string regexEncrypt(const std::string& input);
    std::string regexDecrypt(const std::string& encrypted);
};
