#ifndef SHOP_H
#define SHOP_H

#include <QWidget>
#include <vector>  
#include "circle.h"  

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

    std::vector<Circle*> button1Circles;
    std::vector<Circle*> button2Circles;
    int button1CircleCount = 0;  
    int button2CircleCount = 0; 

private slots:
    void button1Clicked(); 
    void button2Clicked();  
};

#endif // SHOP_H
