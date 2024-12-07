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
    void resetFields();


signals:
    void goToLogin();             
    void registerCredentials(const QString& username, const QString& password); 

private slots:
    void handleRegister();
    //void resetFields();  // Slot pentru resetarea câmpurilor

private:
    QLineEdit* usernameField;
    QLineEdit* passwordField;
    QLineEdit* verifyPasswordField;
    QPushButton* registerButton;
    QLabel* errorLabel;
};

#endif // REGISTERWINDOW_H
