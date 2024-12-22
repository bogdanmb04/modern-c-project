#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget* parent = nullptr);
    ~RegisterWindow();

signals:
    void goToLogin();
    void registerCredentials(const QString& username, const QString& password);

private slots:
    void handleRegister();
    void handleBackToLogin();

private:
    void resetFields();

    QLineEdit* usernameField;
    QLineEdit* passwordField;
    QLineEdit* verifyPasswordField;
    QPushButton* registerButton;
    QPushButton* backToLoginButton;
    QLabel* errorLabel;
};

#endif // REGISTERWINDOW_H
