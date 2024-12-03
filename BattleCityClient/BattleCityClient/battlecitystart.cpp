#include "battlecitystart.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>


BattleCity::BattleCity(QWidget *parent)
    : QWidget(parent) {
    setupUI();
    setWindowTitle("BattleCity");
    //showMaximized();

}

BattleCity::~BattleCity() {
}

void BattleCity::setupUI() {

    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    QVBoxLayout *titleLayout = new QVBoxLayout();
    QLabel *titleLabel1 = new QLabel("Welcome to");
    titleLabel1->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    titleLabel1->setStyleSheet("font-size: 29px; font-weight: bold;");

    QLabel *titleLabel = new QLabel("BattleCity");
    titleLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    titleLabel->setStyleSheet("font-size: 36px; font-weight: bold;");

    titleLayout->addWidget(titleLabel1);
    titleLayout->addWidget(titleLabel);
    mainLayout->addLayout(titleLayout);


      QVBoxLayout *buttonLayout = new QVBoxLayout();
      buttonLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);


    QPushButton *button1 = new QPushButton("Start");
    QPushButton *button2 = new QPushButton("Shop");
    QPushButton *button3 = new QPushButton("Server");


    button1->setFixedSize(200, 50);
    button2->setFixedSize(200, 50);
    button3->setFixedSize(200, 50);


    connect(button1, &QPushButton::clicked, this, &BattleCity::button1Clicked);
    connect(button2, &QPushButton::clicked, this, &BattleCity::button2Clicked);


    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button3);
     buttonLayout->addWidget(button2);


    mainLayout->addLayout(buttonLayout);
}

