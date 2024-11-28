#include "loginwindow.h"
#include <QVBoxLayout>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    // Layout vertical pentru toate elementele
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Label pentru titlu
    QLabel *titleLabel = new QLabel("Login Page", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Câmp pentru nume utilizator
    usernameField = new QLineEdit(this);
    usernameField->setPlaceholderText("Username");
    layout->addWidget(usernameField);

    // Câmp pentru parolă
    passwordField = new QLineEdit(this);
    passwordField->setPlaceholderText("Password");
    passwordField->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordField);

    // Buton pentru logare
    loginButton = new QPushButton("Login", this);
    layout->addWidget(loginButton);

    // Label pentru afișarea erorilor
    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red;");
    errorLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(errorLabel);

    // Conectăm butonul la funcția handleLogin
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);

    // Setăm layout-ul ferestrei
    setLayout(layout);
    setWindowTitle("Login");
    resize(300, 200);
}

LoginWindow::~LoginWindow()
{
}

void LoginWindow::handleLogin()
{
    QString username = usernameField->text();
    QString password = passwordField->text();

    if (username == "admin" && password == "1234") {
        errorLabel->setStyleSheet("color: green;");
        errorLabel->setText("Login successful!");
        emit loginSuccess(); // Emit semnalul pentru logare reușită
    } else {
        errorLabel->setStyleSheet("color: red;");
        errorLabel->setText("Invalid username or password!");
    }
}
