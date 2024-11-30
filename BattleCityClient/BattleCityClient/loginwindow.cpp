#include "loginwindow.h"
#include "registerwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>

// Implementarea LoginWindow
LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("BattleCity", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    layout->addWidget(titleLabel);

    QLabel *loginLabel = new QLabel("Log in", this);
    loginLabel->setAlignment(Qt::AlignCenter);
    loginLabel->setStyleSheet("font-size: 18px;");
    layout->addWidget(loginLabel);

    usernameField = new QLineEdit(this);
    usernameField->setPlaceholderText("Username");
    layout->addWidget(usernameField);

    passwordField = new QLineEdit(this);
    passwordField->setPlaceholderText("Password");
    passwordField->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordField);

    loginButton = new QPushButton("Login", this);
    layout->addWidget(loginButton);

    registerButton = new QPushButton("Don't have an account? Register", this);
    layout->addWidget(registerButton);

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red;");
    errorLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(errorLabel);




    // Conectăm semnalele butoanelor la sloturi
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::goToRegisterPage);

    setLayout(layout);
    setWindowTitle("Login - BattleCity");
    resize(300, 250);
}


LoginWindow::~LoginWindow() {}

void LoginWindow::setUserCredentials(const QString &username, const QString &password)
{
    // Salvează datele de utilizator
    registeredUsername = username;
    registeredPassword = password;

    qDebug() << "Saved credentials in LoginWindow:" << registeredUsername << registeredPassword;
}

void LoginWindow::handleLogin()
{
    QString username = usernameField->text();
    QString password = passwordField->text();

    qDebug() << "Attempting login with:" << username << password;
    qDebug() << "Saved credentials:" << registeredUsername << registeredPassword;

    // Compară username și parola
    if ((username == "admin" && password == "1234") ||
        (username == registeredUsername && password == registeredPassword)) {
        errorLabel->setStyleSheet("color: green;");
        errorLabel->setText("Login successful!");
        emit loginSuccess();  // Emit semnalul de succes
    } else {
        errorLabel->setStyleSheet("color: red;");
        errorLabel->setText("Invalid username or password!");
    }
}

void LoginWindow::goToRegisterPage()
{
    // Creăm fereastra de înregistrare și o afișăm
    RegisterWindow *registerWindow = new RegisterWindow();
    connect(registerWindow, &RegisterWindow::goToLogin, this, &LoginWindow::show); // Conectăm semnalul pentru redirecționare
    connect(registerWindow, &RegisterWindow::registerCredentials,
            this, &LoginWindow::setUserCredentials);  // Conectăm semnalul de înregistrare la setUserCredentials
    registerWindow->show();
    this->close();  // Închidem fereastra de login
}
