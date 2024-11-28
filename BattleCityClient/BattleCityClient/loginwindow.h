#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loginSuccess(); // Semnal emis când logarea reușește

private slots:
    void handleLogin();

private:
    QLineEdit *usernameField;
    QLineEdit *passwordField;
    QLabel *errorLabel;
    QPushButton *loginButton;
};

#endif // LOGINWINDOW_H
