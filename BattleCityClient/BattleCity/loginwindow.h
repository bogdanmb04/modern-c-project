#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include "HttpManager.h"

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget* parent = nullptr);
    ~LoginWindow();

    void setUserCredentials(const QString& username, const QString& password);
    uint32_t getUserId() const;

signals:
    void loginSuccess(uint32_t userId);         
    void goToRegister();         
private slots:
    void handleLogin();          
    void goToRegisterPage();     
private:
    uint32_t userId;

    QString registeredUsername;  
    QString registeredPassword;  
    QLineEdit* usernameField;    
    QLineEdit* passwordField;    
    QLabel* errorLabel;          
    QPushButton* loginButton;    
    QPushButton* registerButton; 
};

#endif // LOGINWINDOW_H
