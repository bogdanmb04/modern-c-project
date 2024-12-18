#include "shop.h"
#include "circle.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QPixmap>
#include <QGroupBox>

Shop::Shop(QWidget* parent) : QWidget(parent), money(0), specialMoney(0), button1CircleCount(0), button2CircleCount(0) {
    setupUI();
}

Shop::~Shop() {}

void Shop::setupUI() {
    setWindowTitle("Shop");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(10);

    QSpacerItem* spacerAboveTitle = new QSpacerItem(60, 60, QSizePolicy::Minimum, QSizePolicy::Fixed);
    mainLayout->addSpacerItem(spacerAboveTitle);

    QLabel* titleLabel = new QLabel("Shop", this);
    titleLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    titleLabel->setStyleSheet("font-size: 50px; font-weight: bold; margin-bottom: 20px;");
    mainLayout->addWidget(titleLabel);

   
    QGroupBox* moneyBox = new QGroupBox(this);
    moneyBox->setStyleSheet("QGroupBox {border: 5px solid black;border-radius: 5px;padding: 5px;background-color:#4f1410;font-size: 20px;}");
    moneyBox->setFixedWidth(170);
    moneyBox->setContentsMargins(20, 5, 5, 5);

    QHBoxLayout* moneyLayout = new QHBoxLayout();
    moneyLayout->setAlignment(Qt::AlignLeft);
    moneyLayout->setContentsMargins(30, 0, 0, 0);

    QLabel* moneyImageLabel = new QLabel(this);
    QPixmap moneyPixmap(":/BattleCity/images/Coins.png");
    moneyPixmap = moneyPixmap.scaled(60, 60, Qt::KeepAspectRatio);
    moneyImageLabel->setPixmap(moneyPixmap);
    moneyImageLabel->setAlignment(Qt::AlignLeft);

    moneyLayout->addWidget(moneyImageLabel);

    QSpacerItem* spacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    moneyLayout->addSpacerItem(spacer);

    moneyLabel = new QLabel(QString::number(money), this);
    moneyLabel->setAlignment(Qt::AlignLeft);
    moneyLabel->setStyleSheet("font-size: 30px;");
    moneyLayout->addWidget(moneyLabel);

    moneyBox->setLayout(moneyLayout);

  
    QGroupBox* specialMoneyBox = new QGroupBox(this);
    specialMoneyBox->setStyleSheet("QGroupBox {border: 5px solid black;border-radius: 5px;padding: 5px;background-color:#4f1410;font-size: 20px;}");
    specialMoneyBox->setFixedWidth(170);
    specialMoneyBox->setContentsMargins(20, 5, 5, 5);

    QHBoxLayout* specialMoneyLayout = new QHBoxLayout();
    specialMoneyLayout->setAlignment(Qt::AlignLeft);
    specialMoneyLayout->setContentsMargins(20, 0, 0, 0);

    specialMoneyImage = new QLabel(this);
    QPixmap specialMoneyPixmap(":/BattleCity/images/SpecialMoney.png");
    specialMoneyPixmap = specialMoneyPixmap.scaled(60, 60, Qt::KeepAspectRatio);
    specialMoneyImage->setPixmap(specialMoneyPixmap);
    specialMoneyImage->setAlignment(Qt::AlignLeft);

    specialMoneyLayout->addWidget(specialMoneyImage);

    QSpacerItem* spacer2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    specialMoneyLayout->addSpacerItem(spacer2);

    specialMoneyLabel = new QLabel(QString::number(specialMoney), this);
    specialMoneyLabel->setStyleSheet("font-size: 30px;");
    specialMoneyLayout->addWidget(specialMoneyLabel);
    specialMoneyLabel->setAlignment(Qt::AlignLeft);
    specialMoneyBox->setLayout(specialMoneyLayout);

    QHBoxLayout* currencyLayout = new QHBoxLayout();
    currencyLayout->addWidget(moneyBox);
    currencyLayout->addWidget(specialMoneyBox);
    currencyLayout->setAlignment(Qt::AlignLeft);
    currencyLayout->setContentsMargins(40, 0, 0, 0);

    mainLayout->addLayout(currencyLayout);

   
    QHBoxLayout* buttonsLayout = new QHBoxLayout();

   
    QVBoxLayout* leftColumn = new QVBoxLayout();
    QGroupBox* button1Group = new QGroupBox(this);
    button1Group->setStyleSheet("QGroupBox {border: none; padding: 0;}");

   
    QVBoxLayout* button1GroupLayout = new QVBoxLayout();

  
    QPushButton* button1 = new QPushButton("Wait Time", this);
    button1->setStyleSheet(
        "font-size: 25px;"
        "text-align: left;"
        "padding-left: 10px;"
    );
    button1->setFixedSize(700, 150);

  
    QWidget* circlesContainer1 = new QWidget(button1);
    circlesContainer1->setGeometry(QRect(0, 0, button1->width(), button1->height()));  

    QHBoxLayout* circlesLayout = new QHBoxLayout(circlesContainer1); 
    circlesLayout->setAlignment(Qt::AlignBottom | Qt::AlignRight);  
    circlesLayout->setSpacing(10);

    QLabel* imageLabel1 = new QLabel(button1); 
    QPixmap imagePixmap(":/BattleCity/images/UpgradeIcon.png"); 
    imagePixmap = imagePixmap.scaled(40, 40, Qt::KeepAspectRatio); 
    imageLabel1->setPixmap(imagePixmap);
    imageLabel1->setAlignment(Qt::AlignCenter);

    circlesLayout->addWidget(imageLabel1); 
    Circle* circle1 = new Circle(this);
    circle1->setFixedSize(20, 20);
    circlesLayout->addWidget(circle1);
     
   
    for (int i = 1; i < 5; ++i) {
        Circle* circle = new Circle(this);
        button1Circles.push_back(circle);
        circle->setFixedSize(20, 20);
        circlesLayout->addWidget(circle);
    }

    button1GroupLayout->addWidget(button1);
    button1Group->setLayout(button1GroupLayout);
    leftColumn->addWidget(button1Group);

   
    QVBoxLayout* rightColumn = new QVBoxLayout();
    QGroupBox* button2Group = new QGroupBox(this);
    button2Group->setStyleSheet("QGroupBox {border: none; padding: 0;}");

    QVBoxLayout* button2GroupLayout = new QVBoxLayout();

    QPushButton* button2 = new QPushButton("Bullet Speed", this);
    button2->setStyleSheet(
        "font-size: 25px;"
        "text-align: left;"
        "padding-left: 10px;"
    );
    button2->setFixedSize(700, 150);

   
    QWidget* circlesContainer2 = new QWidget(button2);
    circlesContainer2->setGeometry(QRect(0, 0, button2->width(), button2->height())); 

    QHBoxLayout* circlesLayout2 = new QHBoxLayout(circlesContainer2); 
    circlesLayout2->setAlignment(Qt::AlignBottom | Qt::AlignRight); 
    circlesLayout2->setSpacing(7);

    
    QLabel* imageLabel2 = new QLabel(button2);
    QPixmap imagePixmap2(":/BattleCity/images/UpgradeIcon.png"); 
    imagePixmap2 = imagePixmap2.scaled(30, 30); 
    imageLabel2->setPixmap(imagePixmap2);
    imageLabel2->setAlignment(Qt::AlignCenter);

     circlesLayout2->addWidget(imageLabel2);
    Circle* circle2 = new Circle(this);
    circle2->setFixedSize(20, 20);
    circlesLayout2->addWidget(circle2);
    

  
    for (int i = 1; i < 5; ++i) {
        Circle* circle = new Circle(this);
        button2Circles.push_back(circle);
        circle->setFixedSize(20, 20);
        circlesLayout2->addWidget(circle);
    }

    button2GroupLayout->addWidget(button2);
    button2Group->setLayout(button2GroupLayout);
    rightColumn->addWidget(button2Group);

    buttonsLayout->addLayout(leftColumn);
    buttonsLayout->addLayout(rightColumn);

    mainLayout->addLayout(buttonsLayout);

    QSpacerItem* spacerBelowButtons = new QSpacerItem(60, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addSpacerItem(spacerBelowButtons);

    connect(button1, &QPushButton::clicked, this, &Shop::button1Clicked);
    connect(button2, &QPushButton::clicked, this, &Shop::button2Clicked);
}

void Shop::button1Clicked() {
    if (button1CircleCount < button1Circles.size()) {
        button1Circles[button1CircleCount]->setFilled(true);
        button1CircleCount++;
    }
    money -= 0; 
    moneyLabel->setText(QString::number(money));
}

void Shop::button2Clicked() {
    if (button2CircleCount < button2Circles.size()) {
        button2Circles[button2CircleCount]->setFilled(true);
        button2CircleCount++;
    }
    specialMoney -= 0; 
    specialMoneyLabel->setText(QString::number(specialMoney));
}
