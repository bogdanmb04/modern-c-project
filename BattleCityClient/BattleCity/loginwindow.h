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

signals:
    void loginSuccess();         
    void goToRegister();         
private slots:
    void handleLogin();          
    void goToRegisterPage();     
private:
    QString registeredUsername;  
    QString registeredPassword;  
    QLineEdit* usernameField;    
    QLineEdit* passwordField;    
    QLabel* errorLabel;          
    QPushButton* loginButton;    
    QPushButton* registerButton; 
};

#endif // LOGINWINDOW_H
