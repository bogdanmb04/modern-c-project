
#include "shop.h"
#include "circle.h"
#include "battlecitystart.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QPixmap>
#include <QGroupBox>
#include <QDebug>
#include <QTimer>

Shop::Shop(QWidget* parent) : QWidget(parent), money(0), specialMoney(0), button1CircleCount(0), button2CircleCount(0) {
    priceButton1 = 25;
    priceButton2 = 20;

    setupUI();
}

Shop::~Shop() {}

void Shop::setupUI() {
    setWindowTitle("Shop");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QPushButton* backButton = new QPushButton("Back", this);
    backButton->setStyleSheet("font-size: 15px; padding: 10px;");
    backButton->setFixedSize(70, 40);

    QPixmap backPixmap(":/BattleCity/images/Back.png");
    backButton->setIcon(QIcon(backPixmap));
    backButton->setIconSize(QSize(10, 10));
    backButton->setText("Back");

    QHBoxLayout* backButtonLayout = new QHBoxLayout();
    backButtonLayout->addWidget(backButton);
    backButtonLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    mainLayout->addLayout(backButtonLayout);

    connect(backButton, &QPushButton::clicked, this, &Shop::BackButtonClicked);

    QLabel* titleLabel = new QLabel("Shop", this);
    titleLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    titleLabel->setStyleSheet("font-size: 50px; font-weight: bold; margin-bottom: 20px;");
    mainLayout->addWidget(titleLabel);

    insufficientFundsLabel = new QLabel("", this);
    insufficientFundsLabel->setAlignment(Qt::AlignCenter);
    insufficientFundsLabel->setStyleSheet("font-size: 20px; color: red;");
    mainLayout->addWidget(insufficientFundsLabel);

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

    QVBoxLayout* buttonsLayout = new QVBoxLayout();

    QPushButton* button1 = new QPushButton("Wait Time", this);
    button1->setStyleSheet("font-size: 25px; text-align: left; padding-left: 10px;");
    button1->setFixedSize(700, 150);

    QPixmap imagePixmap(":/BattleCity/images/UpgradeIcon.png");
    QWidget* circlesContainer1 = new QWidget(button1);
    circlesContainer1->setGeometry(QRect(0, 0, button1->width(), button1->height()));

    QHBoxLayout* circlesLayout = new QHBoxLayout(circlesContainer1);
    circlesLayout->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    circlesLayout->setSpacing(10);

    QLabel* imageLabel1 = new QLabel(button1);
    imagePixmap = imagePixmap.scaled(40, 40, Qt::KeepAspectRatio);
    imageLabel1->setPixmap(imagePixmap);
    imageLabel1->setAlignment(Qt::AlignCenter);
    imageLabel1->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    circlesLayout->addWidget(imageLabel1);

    for (int i = 0; i < 5; ++i) {
        Circle* circle = new Circle(this);
        button1Circles.push_back(circle);
        circle->setFixedSize(20, 20);
        circlesLayout->addWidget(circle);
    }

    QLabel* priceLabel1 = new QLabel(QString::number(priceButton1), this);
    priceLabel1->setStyleSheet("font-size: 16px; font-weight: bold;");
    priceLabel1->setAlignment(Qt::AlignTop | Qt::AlignRight);
    priceLabel1->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    QHBoxLayout* button1Layout = new QHBoxLayout(button1);
    button1Layout->setContentsMargins(0, 0, 0, 0);
    button1Layout->addWidget(priceLabel1, 0, Qt::AlignTop | Qt::AlignRight);

    buttonsLayout->addWidget(button1);

    QPushButton* button2 = new QPushButton("Bullet Speed", this);
    button2->setStyleSheet("font-size: 25px; text-align: left; padding-left: 10px;");
    button2->setFixedSize(700, 150);

    QPixmap imagePixmap2(":/BattleCity/images/UpgradeIcon.png");
    QWidget* circlesContainer2 = new QWidget(button2);
    circlesContainer2->setGeometry(QRect(0, 0, button2->width(), button2->height()));

    QHBoxLayout* circlesLayout2 = new QHBoxLayout(circlesContainer2);
    circlesLayout2->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    circlesLayout2->setSpacing(7);

    QLabel* imageLabel2 = new QLabel(button2);
    imagePixmap2 = imagePixmap2.scaled(40, 40, Qt::KeepAspectRatio);
    imageLabel2->setPixmap(imagePixmap2);
    imageLabel2->setAlignment(Qt::AlignCenter);
    imageLabel2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    circlesLayout2->addWidget(imageLabel2);

    for (int i = 0; i < 5; ++i) {
        Circle* circle = new Circle(this);
        button2Circles.push_back(circle);
        circle->setFixedSize(20, 20);
        circlesLayout2->addWidget(circle);
    }

    QLabel* priceLabel2 = new QLabel(QString::number(priceButton2), this);
    priceLabel2->setStyleSheet("font-size: 16px; font-weight: bold; padding-left: 10px;");
    priceLabel2->setAlignment(Qt::AlignTop | Qt::AlignRight);
    priceLabel2->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    QHBoxLayout* button2Layout = new QHBoxLayout(button2);
    button2Layout->setContentsMargins(0, 0, 0, 0);
    button2Layout->addWidget(priceLabel2, 0, Qt::AlignTop | Qt::AlignRight);

    buttonsLayout->addWidget(button2);

    buttonsLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(buttonsLayout);

    QSpacerItem* spacerBelowButtons = new QSpacerItem(60, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addSpacerItem(spacerBelowButtons);
}

void Shop::button1Clicked() {
    if (money >= priceButton1) {
        if (button1CircleCount < button1Circles.size()) {
            button1Circles[button1CircleCount]->setFilled(true);
            button1CircleCount++;
        }
        money -= priceButton1;
        moneyLabel->setText(QString::number(money));
        insufficientFundsLabel->clear();
    }
    else {
        insufficientFundsLabel->setText("Insufficient funds");
        QTimer::singleShot(2000, this, [this]() {
            insufficientFundsLabel->clear();
            });
    }
}

void Shop::button2Clicked() {
    if (money >= priceButton2) {
        if (button2CircleCount < button2Circles.size()) {
            button2Circles[button2CircleCount]->setFilled(true);
            button2CircleCount++;
        }
        money -= priceButton2;
        moneyLabel->setText(QString::number(money));
        insufficientFundsLabel->clear();
    }
    else {
        insufficientFundsLabel->setText("Insufficient funds");
        QTimer::singleShot(2000, this, [this]() {
            insufficientFundsLabel->clear();
            });
    }
}
void Shop::onBackButtonClicked()
{
    emit backToBattleCity();
    this->close();
}

void Shop::BackButtonClicked() {
    emit backToBattleCity();
    this->close();
}
