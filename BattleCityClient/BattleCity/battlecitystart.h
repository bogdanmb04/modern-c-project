#ifndef BATTLECITYSTART_H
#define BATTLECITYSTART_H

#include <QWidget>

class QPushButton;
class CharacterSelection;
class MainWindow;

class BattleCity : public QWidget {
    Q_OBJECT

public:
    void setUserId(const QString& userId) {
        this->userId = userId;
    }
    explicit BattleCity(QWidget* parent = nullptr);
    ~BattleCity();

signals:
    void button1Clicked();
    void button2Clicked();
    void button3Clicked();
    void button4Clicked();
    void gameStarted(const QString& userId);

private slots:
    void onButton1Clicked();
    void onCharacterChosen(const QString& character);

private:
    QString userId;

    void setupUI();
    QPushButton* button1;
    QPushButton* button2;
    QPushButton* button3;
    QPushButton* button4;
    MainWindow* mainWindow;
};

#endif // BATTLECITYSTART_H
