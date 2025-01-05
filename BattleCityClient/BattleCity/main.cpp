#include "mainwindow.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include "battlecitystart.h"
#include "shop.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    LoginWindow loginWindow;
    MainWindow mainWindow;
    RegisterWindow registerWindow;
    BattleCity battleCityWindow;
    Shop shop;

    QObject::connect(&mainWindow, &MainWindow::backToBattleCity, [&]() {
        mainWindow.close();
        battleCityWindow.showFullScreen();
        });

    QObject::connect(&loginWindow, &LoginWindow::loginSuccess, [&]() {
        loginWindow.close();
        battleCityWindow.showFullScreen();
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
        mainWindow.showFullScreen();
        });

    QObject::connect(&battleCityWindow, &BattleCity::button2Clicked, [&]() {
        battleCityWindow.close();
        shop.showFullScreen();
        });

    QObject::connect(&shop, &Shop::backToBattleCity, [&]() {
        shop.close();
        battleCityWindow.showFullScreen();
        });

    loginWindow.show();

    return a.exec();
}
