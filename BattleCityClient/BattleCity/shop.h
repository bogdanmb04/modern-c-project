#ifndef SHOP_H
#define SHOP_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <vector>

class Circle;  

class Shop : public QWidget {
    Q_OBJECT

public:
    explicit Shop(QWidget* parent = nullptr);
    ~Shop();

      
public slots:
    void onBackButtonClicked();
signals:
    void backToBattleCity(); 

private:
    void setupUI(); 
    void BackButtonClicked();  
    QLabel* moneyLabel;
    QLabel* specialMoneyLabel;
    QLabel* insufficientFundsLabel;
    QLabel* specialMoneyImage;
    int money;
    int specialMoney;
    int priceButton1;
    int priceButton2;
    int button1CircleCount;
    int button2CircleCount;
    std::vector<Circle*> button1Circles;
    std::vector<Circle*> button2Circles;

private slots:
    void button1Clicked();  
    void button2Clicked(); 
};

#endif // SHOP_H
