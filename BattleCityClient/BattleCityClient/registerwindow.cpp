#include "registerwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

// Implementarea RegisterWindow
RegisterWindow::RegisterWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("BattleCity", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    layout->addWidget(titleLabel);

    QLabel *registerLabel = new QLabel("Register", this);
    registerLabel->setAlignment(Qt::AlignCenter);
    registerLabel->setStyleSheet("font-size: 18px;");
    layout->addWidget(registerLabel);

    usernameField = new QLineEdit(this);
    usernameField->setPlaceholderText("Username");
    layout->addWidget(usernameField);

    passwordField = new QLineEdit(this);
    passwordField->setPlaceholderText("Password");
    passwordField->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordField);

    verifyPasswordField = new QLineEdit(this);
    verifyPasswordField->setPlaceholderText("Verify Password");
    verifyPasswordField->setEchoMode(QLineEdit::Password);
    layout->addWidget(verifyPasswordField);

    registerButton = new QPushButton("Register", this);
    layout->addWidget(registerButton);

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red;");
    errorLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(errorLabel);

    // Conectăm butonul de înregistrare la slotul de handleRegister
    connect(registerButton, &QPushButton::clicked, this, &RegisterWindow::handleRegister);

    setLayout(layout);
    setWindowTitle("Register - BattleCity");
    resize(300, 300);
}

RegisterWindow::~RegisterWindow() {}

void RegisterWindow::handleRegister()
{
    QString username = usernameField->text();
    QString password = passwordField->text();
    QString verifyPassword = verifyPasswordField->text();

    if (username.isEmpty() || password.isEmpty() || verifyPassword.isEmpty()) {
        errorLabel->setText("All fields are required!");
        return;
    }

    if (password != verifyPassword) {
        errorLabel->setText("Passwords do not match!");
        return;
    }

    // Verifică dacă câmpurile nu sunt goale și emite semnalul
    qDebug() << "Emitting register credentials:" << username << password;
    emit registerCredentials(username, password);  // Emit semnalul

    errorLabel->setStyleSheet("color: green;");
    errorLabel->setText("Registration successful!");
    this->close();
    emit goToLogin();  // Treci înapoi la LoginWindow

}

void RegisterWindow::resetFields()
{
    // Resetează câmpurile
    usernameField->clear();
    passwordField->clear();
    verifyPasswordField->clear();
    errorLabel->clear();  // Curăță mesajele de eroare
}
