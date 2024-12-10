#ifndef SHOP_H
#define SHOP_H

#include <QWidget>

class Shop : public QWidget {
    Q_OBJECT

public:
    explicit Shop(QWidget* parent = nullptr);
    ~Shop();

signals:
    void button1Clicked();
    void button2Clicked();
    void button3Clicked();
    void button4Clicked();
    void button5Clicked();
    void button6Clicked();

private:
    void setupUI();
};

#endif // SHOP_H
