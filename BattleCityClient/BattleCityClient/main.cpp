#include "mainwindow.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow loginWindow;  // Fereastra de login
    MainWindow mainWindow;    // Fereastra principală
    RegisterWindow registerWindow; // Fereastra de înregistrare

    // Conectează semnalul de succes al loginului cu slotul de deschidere a ferestrei principale
    QObject::connect(&loginWindow, &LoginWindow::loginSuccess, [&]() {
        loginWindow.close();  // Închide fereastra de login
        mainWindow.show();    // Afișează fereastra principală
    });

    // Conectează semnalul goToLogin al RegisterWindow pentru a întoarce utilizatorul la LoginWindow
    QObject::connect(&registerWindow, &RegisterWindow::goToLogin, [&]() {
        registerWindow.close();  // Închide fereastra de înregistrare
        loginWindow.show();      // Afișează fereastra de login
    });

    // Conectează loginWindow și registerWindow pentru a permite trecerea între feronstrele de login și înregistrare
    QObject::connect(&loginWindow, &LoginWindow::goToRegister, [&]() {
        loginWindow.close();  // Închide fereastra de login
        registerWindow.show(); // Afișează fereastra de înregistrare
    });

    // Conectează semnalul de înregistrare din RegisterWindow pentru a salva credențialele în LoginWindow
    QObject::connect(&registerWindow, &RegisterWindow::registerCredentials,
                     &loginWindow, &LoginWindow::setUserCredentials);

    loginWindow.show();  // Afișează fereastra de login la început

    return a.exec();  // Rulează aplicația
}
