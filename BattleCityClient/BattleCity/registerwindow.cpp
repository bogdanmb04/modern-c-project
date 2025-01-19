#include "registerwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>
#include <QDebug>
#include "HttpManager.h"
#include <cpr/cpr.h>
#include <QPalette>
#include <QPixmap>
#include "resources.h"

RegisterWindow::RegisterWindow(QWidget* parent)
    : QWidget(parent)
{
    QPixmap background(Constants::kIntro);
    background = background.scaled(500, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    setPalette(palette);


    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(100, 100, 100, 100);

    QLabel* titleLabel = new QLabel("BattleCity", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    layout->addWidget(titleLabel);

    QLabel* registerLabel = new QLabel("Register", this);
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

    backToLoginButton = new QPushButton("Back to Login", this);
    layout->addWidget(backToLoginButton);

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red;");
    errorLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(errorLabel);

    connect(registerButton, &QPushButton::clicked, this, &RegisterWindow::handleRegister);
    connect(backToLoginButton, &QPushButton::clicked, this, &RegisterWindow::handleBackToLogin);

    setLayout(layout);
    setWindowTitle("Register - BattleCity");
    setFixedSize(500, 400);
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

    QString jsonData = QString("{\"username\":\"%1\", \"password\":\"%2\"}")
        .arg(username)
        .arg(password);
    QByteArray byteArray = jsonData.toUtf8();

    cpr::Response response = cpr::Post(
        cpr::Url{ "http://localhost:18080/register" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ byteArray }
    );

    qDebug() << "Status code: " << response.status_code;
    qDebug() << "Server response: " << QString::fromStdString(response.text);

    if (response.status_code == 201) {
        qDebug() << "Registration successful!";
        emit registerCredentials(username, password);
        errorLabel->setStyleSheet("color: green;");
        errorLabel->setText("Registration successful!");
        QTimer::singleShot(1500, this, &RegisterWindow::close);
        emit goToLogin();
    }
    else if (response.status_code == 400) {
        errorLabel->setStyleSheet("color: red;");
        errorLabel->setText("Error: Username already exists or invalid input.");
    }
    else if (response.status_code == 0) {
        errorLabel->setStyleSheet("color: red;");
        errorLabel->setText("Network error: Server not reachable.");
    }
    else {
        errorLabel->setStyleSheet("color: red;");
        errorLabel->setText("An unexpected error occurred: " + QString::fromStdString(response.text));
    }
}

void RegisterWindow::resetFields()
{
    usernameField->clear();
    passwordField->clear();
    verifyPasswordField->clear();
    errorLabel->clear();
}

void RegisterWindow::handleBackToLogin()
{
    emit goToLogin();
    this->close();
}
