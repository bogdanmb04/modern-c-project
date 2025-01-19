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
#include <cpr/cpr.h>
#include "httpmanager.h"
#include <nlohmann/json.hpp>
#include "resources.h"

Shop::Shop(QWidget* parent)
    : QWidget(parent)
    , userId(QString())
    , coins(0)
    , specialMoney(0)
    , money(0)
    , button1CircleCount(0)
    , button2CircleCount(0) {
    priceButton1 = 500;
    priceButton2 = 10;
    setupUI();
}

Shop::~Shop() {}

void Shop::setupUI() {
    setWindowTitle("Shop");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QPushButton* backButton = new QPushButton("Back", this);
    backButton->setStyleSheet("font-size: 15px; padding: 10px;");
    backButton->setFixedSize(70, 40);

    QPixmap backPixmap(Constants::kBack);
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
    QSpacerItem* topSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addSpacerItem(topSpacer);
    insufficientFundsLabel = new QLabel("", this);
    insufficientFundsLabel->setAlignment(Qt::AlignCenter);
    insufficientFundsLabel->setStyleSheet("font-size: 20px; color: red;");
    mainLayout->addWidget(insufficientFundsLabel);

    QGroupBox* coinsBox = new QGroupBox(this);
    coinsBox->setStyleSheet("QGroupBox {border: 5px solid black;border-radius: 5px;padding: 5px;background-color:#4f1410;font-size: 20px;}");
    coinsBox->setFixedWidth(170);
    coinsBox->setContentsMargins(5, 5, 5, 5);

    QHBoxLayout* coinsLayout = new QHBoxLayout();
    coinsLayout->setAlignment(Qt::AlignTop);
    coinsLayout->setContentsMargins(0, 0, 0, 0);

    QLabel* coinsImageLabel = new QLabel(this);
    QPixmap coinsPixmap(Constants::kCoin);
    coinsPixmap = coinsPixmap.scaled(60, 60, Qt::KeepAspectRatio);
    coinsImageLabel->setPixmap(coinsPixmap);
    coinsImageLabel->setAlignment(Qt::AlignLeft);

    coinsLayout->addWidget(coinsImageLabel);

    QSpacerItem* spacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    coinsLayout->addSpacerItem(spacer);

    coinsLabel = new QLabel(QString::number(money), this);
    coinsLabel->setAlignment(Qt::AlignLeft);
    coinsLabel->setStyleSheet("font-size: 30px;");
    coinsLayout->addWidget(coinsLabel);

    coinsBox->setLayout(coinsLayout);

    QGroupBox* moneyBox = new QGroupBox(this);
    moneyBox->setStyleSheet("QGroupBox {border: 5px solid black;border-radius: 5px;padding: 5px;background-color:#4f1410;font-size: 20px;}");

    moneyBox->setFixedWidth(170);
    moneyBox->setContentsMargins(20, 5, 5, 5);

    QHBoxLayout* moneyLayout = new QHBoxLayout();
    moneyLayout->setAlignment(Qt::AlignTop);
    moneyLayout->setContentsMargins(20, 0, 0, 0);

    specialMoneyImage = new QLabel(this);
    QPixmap specialMoneyPixmap(Constants::kSpecialMoney);
    specialMoneyPixmap = specialMoneyPixmap.scaled(60, 60, Qt::KeepAspectRatio);
    specialMoneyImage->setPixmap(specialMoneyPixmap);
    specialMoneyImage->setAlignment(Qt::AlignLeft);

    moneyLayout->addWidget(specialMoneyImage);

    QSpacerItem* spacer2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    moneyLayout->addSpacerItem(spacer2);

    specialMoneyLabel = new QLabel(QString::number(specialMoney), this);
    specialMoneyLabel->setStyleSheet("font-size: 30px;");
    moneyLayout->addWidget(specialMoneyLabel);
    specialMoneyLabel->setAlignment(Qt::AlignLeft);
    moneyBox->setLayout(moneyLayout);

    QHBoxLayout* currencyLayout = new QHBoxLayout();
    currencyLayout->addWidget(coinsBox);
    currencyLayout->addWidget(moneyBox);
    currencyLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    currencyLayout->setContentsMargins(40, 0, 0, 0);

    mainLayout->addLayout(currencyLayout);

    QVBoxLayout* buttonsLayout = new QVBoxLayout();

    QPushButton* button1 = new QPushButton("Wait Time", this);
    button1->setStyleSheet("font-size: 25px; text-align: left; padding-left: 10px;");
    button1->setFixedSize(700, 150);

    QPixmap imagePixmap(Constants::kUpgradeIcon);
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

    QPixmap imagePixmap2(Constants::kUpgradeIcon);
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

    connect(button1, &QPushButton::clicked, this, &Shop::onButton1Clicked);
    connect(button2, &QPushButton::clicked, this, &Shop::onButton2Clicked);
}

void Shop::BackButtonClicked() {
    emit backToBattleCity();
}


void Shop::getTotalScore() {
    QString url = QString("http://localhost:18080/get/total-score?userId=%1").arg(userId);
    qDebug() << "Fetching total score for userId:" << userId;

    httpManager.sendGetRequest(
        url,
        [this](const cpr::Response& response) {
            if (response.status_code == 200) {
                try {
                    nlohmann::json jsonResponse = nlohmann::json::parse(response.text);
                    if (jsonResponse.contains("totalScore")) {
                        money = jsonResponse["totalScore"].get<int>();
                        coinsLabel->setText(QString::number(money));
                        qDebug() << "Updated total score:" << money;
                    }
                    else {
                        qDebug() << "totalScore field is missing in response.";
                        insufficientFundsLabel->setText("Invalid response data");
                        insufficientFundsLabel->setVisible(true);
                        QTimer::singleShot(1000, this, [this]() {
                            insufficientFundsLabel->setVisible(false);
                            });
                    }
                }
                catch (const std::exception& e) {
                    qDebug() << "Error parsing response:" << e.what();
                    insufficientFundsLabel->setText("Failed to parse response");
                    insufficientFundsLabel->setVisible(true);
                    QTimer::singleShot(1000, this, [this]() {
                        insufficientFundsLabel->setVisible(false);
                        });
                }
            }
            else {
                qDebug() << "GET request failed with status code:" << response.status_code;
                insufficientFundsLabel->setText("Failed to fetch total score");
                insufficientFundsLabel->setVisible(true);
                QTimer::singleShot(1000, this, [this]() {
                    insufficientFundsLabel->setVisible(false);
                    });
            }
        }
    );
}

void Shop::getSpecialMoney() {
    QString url = QString("http://localhost:18080/get/specialMoney?userId=%1").arg(userId);
    qDebug() << "Fetching special money for userId:" << userId;

    httpManager.sendGetRequest(
        url,
        [this](const cpr::Response& response) {
            if (response.status_code == 200) {
                try {
                    nlohmann::json jsonResponse = nlohmann::json::parse(response.text);
                    if (jsonResponse.contains("specialMoney")) {
                        specialMoney = jsonResponse["specialMoney"].get<int>();
                        specialMoneyLabel->setText(QString::number(specialMoney));
                        qDebug() << "Updated special money:" << specialMoney;
                    }
                    else {
                        qDebug() << "specialMoney field is missing in response.";
                        insufficientFundsLabel->setText("Invalid response data");
                        insufficientFundsLabel->setVisible(true);
                        QTimer::singleShot(1000, this, [this]() {
                            insufficientFundsLabel->setVisible(false);
                            });
                    }
                }
                catch (const std::exception& e) {
                    qDebug() << "Error parsing response:" << e.what();
                    insufficientFundsLabel->setText("Failed to parse response");
                    insufficientFundsLabel->setVisible(true);
                    QTimer::singleShot(1000, this, [this]() {
                        insufficientFundsLabel->setVisible(false);
                        });
                }
            }
            else {
                qDebug() << "GET request failed with status code:" << response.status_code;
                insufficientFundsLabel->setText("Failed to fetch special money");
                insufficientFundsLabel->setVisible(true);
                QTimer::singleShot(1000, this, [this]() {
                    insufficientFundsLabel->setVisible(false);
                    });
            }
        }
    );
}

void Shop::onButton1Clicked() {
    if (userId == '0') {
        qDebug() << "Warning: userId not set!";
        return;
    }

    qDebug() << "Button 1 clicked, current money:" << money;
    getTotalScore();

    if (money >= priceButton1) {
        nlohmann::json requestData;
        requestData["userId"] = userId.toStdString();

        httpManager.sendPostRequest(
            "http://localhost:18080/upgrade/bullet-wait-time",
            QString::fromStdString(requestData.dump()),
            [this](const cpr::Response& response) {
                if (response.status_code == 200) {
                    money -= priceButton1;
                    coinsLabel->setText(QString::number(money));
                    button1CircleCount++;
                    for (int i = 0; i < button1CircleCount; ++i) {
                        button1Circles[i]->setVisible(true);
                    }
                    qDebug() << "Upgrade successful, new money:" << money;
                }
                else {
                    qDebug() << "Upgrade failed with status code:" << response.status_code;
                    insufficientFundsLabel->setText("Upgrade failed!");
                    insufficientFundsLabel->setVisible(true);
                    QTimer::singleShot(1000, this, [this]() {
                        insufficientFundsLabel->setVisible(false);
                        });
                }
            }
        );
    }
    else {
        qDebug() << "Insufficient funds for upgrade. Required:" << priceButton1 << "Available:" << money;
        insufficientFundsLabel->setText("Insufficient funds");
        insufficientFundsLabel->setVisible(true);
        QTimer::singleShot(1000, this, [this]() {
            insufficientFundsLabel->setVisible(false);
            });
    }
}

void Shop::onButton2Clicked() {
    if (userId == "0") {
        qDebug() << "Warning: userId not set!";
        return;
    }

    getSpecialMoney();

    if (specialMoney >= priceButton2) {
        nlohmann::json requestData;
        requestData["userId"] = userId.toStdString();

        httpManager.sendPostRequest(
            "http://localhost:18080/upgrade/bullet-speed",
            QString::fromStdString(requestData.dump()),
            [this](const cpr::Response& response) {
                if (response.status_code == 200) {
                    specialMoney -= priceButton2;
                    specialMoneyLabel->setText(QString::number(specialMoney));
                    button2CircleCount++;
                    for (int i = 0; i < button2CircleCount; ++i) {
                        button2Circles[i]->setVisible(true);
                    }
                    qDebug() << "Upgrade successful, new special money:" << specialMoney;
                }
                else {
                    qDebug() << "Upgrade failed with status code:" << response.status_code;
                    insufficientFundsLabel->setText("Upgrade failed!");
                    insufficientFundsLabel->setVisible(true);
                    QTimer::singleShot(1000, this, [this]() {
                        insufficientFundsLabel->setVisible(false);
                        });
                }
            }
        );
    }
    else {
        qDebug() << "Insufficient special money for upgrade. Required:" << priceButton2 << "Available:" << specialMoney;
        insufficientFundsLabel->setText("Insufficient funds");
        insufficientFundsLabel->setVisible(true);
        QTimer::singleShot(1000, this, [this]() {
            insufficientFundsLabel->setVisible(false);
            });
    }
}
