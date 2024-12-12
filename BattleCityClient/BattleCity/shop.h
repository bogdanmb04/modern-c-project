#ifndef SHOP_H
#define SHOP_H

#include <QWidget>

class QLabel;
class QPushButton;

class Shop : public QWidget
{
    Q_OBJECT

public:
    explicit Shop(QWidget* parent = nullptr);
    ~Shop();

private:
    void setupUI();

    QLabel* moneyLabel;     
    QLabel* specialMoneyLabel; 
    QLabel* specialMoneyImage;

    int money;  
    int specialMoney;

private slots:
    void button1Clicked();
    void button2Clicked();
    void button3Clicked();
    void button4Clicked();
    void button5Clicked();
    void button6Clicked();
};

#endif // SHOP_H
