#include "loginwindow.h"
#include "HttpManager.h"
#include "registerwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>
#include <QPalette>
#include <QPixmap>

LoginWindow::LoginWindow(QWidget* parent)
    : QWidget(parent)
{

    QPixmap background(":/BattleCity/images/Intro2.png");
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

    QLabel* loginLabel = new QLabel("Log in", this);
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

    
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::goToRegisterPage);

    setLayout(layout);
    setWindowTitle("Login - BattleCity");
    setFixedSize(500, 400);
}

LoginWindow::~LoginWindow() {}

void LoginWindow::setUserCredentials(const QString& username, const QString& password)
{
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

    HttpManager httpManager;
    QString loginData = QString("{\"username\":\"%1\",\"password\":\"%2\"}").arg(username).arg(password);

    httpManager.sendPostRequest("http://localhost:18080/login", loginData, [this](const cpr::Response& response) {
        if (response.status_code == 200) {
            errorLabel->setStyleSheet("color: green;");
            errorLabel->setText("Login successful!");
            emit loginSuccess();
        }
        else {
            errorLabel->setStyleSheet("color: red;");
            errorLabel->setText("Invalid username or password!");
        }
        });
}

void LoginWindow::goToRegisterPage()
{
    
    RegisterWindow* registerWindow = new RegisterWindow();
    connect(registerWindow, &RegisterWindow::goToLogin, this, &LoginWindow::show); 
    connect(registerWindow, &RegisterWindow::registerCredentials,
        this, &LoginWindow::setUserCredentials);  
    registerWindow->show();
    this->close();  
}
