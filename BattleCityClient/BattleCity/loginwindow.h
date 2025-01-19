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
    void setUserId(QString id);
    ~LoginWindow();

    void setUserCredentials(const QString& username, const QString& password);
    QString getUserId() const;

signals:
    void loginSuccess(const QString& userId);
    void goToRegister();         
private slots:
    void handleLogin();          
    void goToRegisterPage();     
private:
    QString userId;

    QString registeredUsername;  
    QString registeredPassword;  
    QLineEdit* usernameField;    
    QLineEdit* passwordField;    
    QLabel* errorLabel;          
    QPushButton* loginButton;    
    QPushButton* registerButton; 
};

#endif // LOGINWINDOW_H
