#include "shop.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QPixmap>
#include <QGroupBox>

Shop::Shop(QWidget* parent) : QWidget(parent), money(0), specialMoney(0) {
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
    QPushButton* button1 = new QPushButton("Upgrade 1", this);
    QPushButton* button2 = new QPushButton("Upgrade 2", this);
    QPushButton* button3 = new QPushButton("Upgrade 3", this);

    button1->setFixedSize(700, 150);
    button2->setFixedSize(700, 150);
    button3->setFixedSize(700, 150);

    leftColumn->addWidget(button1);
    leftColumn->addWidget(button2);
    leftColumn->addWidget(button3);

    QVBoxLayout* rightColumn = new QVBoxLayout();
    QPushButton* button4 = new QPushButton("Upgrade 4", this);
    QPushButton* button5 = new QPushButton("Upgrade 5", this);
    QPushButton* button6 = new QPushButton("Upgrade 6", this);

    button4->setFixedSize(700, 150);
    button5->setFixedSize(700, 150);
    button6->setFixedSize(700, 150);

    rightColumn->addWidget(button4);
    rightColumn->addWidget(button5);
    rightColumn->addWidget(button6);

    buttonsLayout->addLayout(leftColumn);
    buttonsLayout->addLayout(rightColumn);

    mainLayout->addLayout(buttonsLayout);

   
    QSpacerItem* spacerBelowButtons = new QSpacerItem(60, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addSpacerItem(spacerBelowButtons);

 
    connect(button1, &QPushButton::clicked, this, &Shop::button1Clicked);
    connect(button2, &QPushButton::clicked, this, &Shop::button2Clicked);
    connect(button3, &QPushButton::clicked, this, &Shop::button3Clicked);
    connect(button4, &QPushButton::clicked, this, &Shop::button4Clicked);
    connect(button5, &QPushButton::clicked, this, &Shop::button5Clicked);
    connect(button6, &QPushButton::clicked, this, &Shop::button6Clicked);
}

void Shop::button1Clicked() {
    money -= 0;
    moneyLabel->setText(QString::number(money));
}

void Shop::button2Clicked() {
    specialMoney -= 0;
    specialMoneyLabel->setText(QString::number(specialMoney));
}

void Shop::button3Clicked() {
    specialMoney -= 0;
    specialMoneyLabel->setText(QString::number(specialMoney));
}

void Shop::button4Clicked() {
    specialMoney -= 0;
    specialMoneyLabel->setText(QString::number(specialMoney));
}

void Shop::button5Clicked() {
    specialMoney -= 0;
    specialMoneyLabel->setText(QString::number(specialMoney));
}

void Shop::button6Clicked() {
    specialMoney -= 0;
    specialMoneyLabel->setText(QString::number(specialMoney));
}
