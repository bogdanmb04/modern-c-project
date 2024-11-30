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

    void setUserCredentials(const QString& username, const QString& password);  // Setter pentru credențiale

signals:
    void loginSuccess();         // Semnal pentru succesul autentificării
    void goToRegister();         // Semnal pentru a naviga către fereastra de înregistrare

private slots:
    void handleLogin();          // Slot pentru procesul de login
    void goToRegisterPage();     // Slot pentru a naviga către fereastra de înregistrare

private:
    QString registeredUsername;  // Username-ul înregistrat
    QString registeredPassword;  // Parola înregistrată
    QLineEdit *usernameField;    // Câmpul de text pentru username
    QLineEdit *passwordField;    // Câmpul de text pentru parolă
    QLabel *errorLabel;          // Eticheta pentru mesaje de eroare
    QPushButton *loginButton;    // Butonul pentru autentificare
    QPushButton *registerButton; // Butonul pentru navigarea către fereastra de înregistrare


};


#endif // LOGINWINDOW_H
