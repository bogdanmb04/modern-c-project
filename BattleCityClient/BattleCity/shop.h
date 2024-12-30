#ifndef SHOP_H
#define SHOP_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVector>

class Circle;

class Shop : public QWidget
{
    Q_OBJECT

public:
    explicit Shop(QWidget *parent = nullptr);
    ~Shop();

private:
    void setupUI();
    
    void onButton1Clicked();
    void onButton2Clicked();
    void BackButtonClicked();

    QPushButton* backButton;
    QPushButton* button1;
    QPushButton* button2;

    QLabel* coinsLabel;
    QLabel* moneyLabel;
    QLabel* specialMoneyLabel;
    QLabel* insufficientFundsLabel;
    QLabel* moneyImageLabel;
    QLabel* specialMoneyImage;

    QVector<Circle*> button1Circles;
    QVector<Circle*> button2Circles;

    int money;
    int specialMoney;
    int coins;
    int button1CircleCount;
    int button2CircleCount;

    int priceButton1;
    int priceButton2;

signals:
    void backToBattleCity();
};

#endif // SHOP_H
