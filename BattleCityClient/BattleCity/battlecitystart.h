#ifndef BATTLECITYSTART_H
#define BATTLECITYSTART_H

#include <QWidget>

class BattleCity : public QWidget {
    Q_OBJECT

public:
    explicit BattleCity(QWidget* parent = nullptr);
    ~BattleCity();

signals:
    void button1Clicked();
    void button2Clicked();
    void button3Clicked();
    void button4Clicked();

private:
    void setupUI();
};

#endif // BATTLECITYSTART_H
