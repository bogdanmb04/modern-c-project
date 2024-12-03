#include "mainwindow.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include "battlecitystart.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow loginWindow;
    MainWindow mainWindow;
    RegisterWindow registerWindow;
    BattleCity battleCityWindow;





    QObject::connect(&loginWindow, &LoginWindow::loginSuccess, [&]() {
        loginWindow.close();
        battleCityWindow.show();
    });


    QObject::connect(&registerWindow, &RegisterWindow::registerCredentials, [&]() {
        registerWindow.close();
    });


    QObject::connect(&loginWindow, &LoginWindow::goToRegister, [&]() {
        loginWindow.close();
        registerWindow.show();
    });


    QObject::connect(&registerWindow, &RegisterWindow::goToLogin, [&]() {
        registerWindow.close();
        loginWindow.show();
    });
    QObject::connect(&battleCityWindow, &BattleCity::button1Clicked, [&]() {
        battleCityWindow.close();
        mainWindow.show();
    });


    loginWindow.show();

    return a.exec();
}
