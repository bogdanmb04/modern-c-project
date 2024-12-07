#ifndef BATTLECITYSTART_H
#define BATTLECITYSTART_H

#include <QWidget>

class BattleCity : public QWidget {
    Q_OBJECT

public:
    explicit BattleCity(QWidget* parent = nullptr);
    ~BattleCity();

signals:
    void button1Clicked(); // Semnal pentru butonul 1
    void button2Clicked(); // Semnal pentru butonul 2

private:
    void setupUI();
};

#endif // BATTLECITYSTART_H
