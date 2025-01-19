#ifndef SHOP_H
#define SHOP_H

#include <QWidget>
#include <QLabel>
#include "circle.h"
#include "httpmanager.h"
#include <vector>

class Shop : public QWidget {
    Q_OBJECT

public:
    explicit Shop(QWidget* parent = nullptr);
    ~Shop();
    void setupUI();

public slots:
    void setUserId(const QString& userId) {
        this->userId = userId;
    }

signals:
    void backToBattleCity();

private slots:
    void BackButtonClicked();
    void onButton1Clicked();
    void onButton2Clicked();

private:
    void getTotalScore();
    void getSpecialMoney();

    QString userId;
    int coins;
    int specialMoney;
    int money;
    int priceButton1;
    int priceButton2;
    int button1CircleCount;
    int button2CircleCount;

    QLabel* coinsLabel;
    QLabel* specialMoneyLabel;
    QLabel* insufficientFundsLabel;
    QLabel* specialMoneyImage;
    std::vector<Circle*> button1Circles;
    std::vector<Circle*> button2Circles;
    HttpManager httpManager;
};

#endif // SHOP_H