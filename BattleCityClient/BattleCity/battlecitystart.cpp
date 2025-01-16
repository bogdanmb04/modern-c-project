#include "battlecitystart.h"
#include "CharacterSelection.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QDebug>

BattleCity::BattleCity(QWidget* parent)
    : QWidget(parent) {
    setupUI();
    setWindowTitle("BattleCity");
}

BattleCity::~BattleCity() {}

void BattleCity::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QVBoxLayout* titleLayout = new QVBoxLayout();
    QLabel* titleLabel1 = new QLabel("Welcome to");
    titleLabel1->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    titleLabel1->setStyleSheet("font-size: 29px; font-weight: bold;");

    QLabel* titleLabel = new QLabel("BattleCity");
    titleLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    titleLabel->setStyleSheet("font-size: 36px; font-weight: bold;");

    titleLayout->addWidget(titleLabel1);
    titleLayout->addWidget(titleLabel);
    mainLayout->addLayout(titleLayout);

    QVBoxLayout* buttonLayout = new QVBoxLayout();
    buttonLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    button1 = new QPushButton("Start");
    button2 = new QPushButton("Shop");
    button3 = new QPushButton("Server");
    button4 = new QPushButton("Quit game");

    button1->setFixedSize(300, 70);
    button2->setFixedSize(300, 70);
    button3->setFixedSize(300, 70);
    button4->setFixedSize(300, 70);

    connect(button1, &QPushButton::clicked, this, &BattleCity::onButton1Clicked);
    connect(button2, &QPushButton::clicked, this, &BattleCity::button2Clicked);
    connect(button3, &QPushButton::clicked, this, &BattleCity::button3Clicked);
    connect(button4, &QPushButton::clicked, qApp, &QApplication::quit);

    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);
    buttonLayout->addWidget(button3);
    buttonLayout->addWidget(button4);

    mainLayout->addLayout(buttonLayout);
}

void BattleCity::onButton1Clicked() {

    CharacterSelection* dialog = new CharacterSelection(this);
    connect(dialog, &CharacterSelection::characterChosen, this, &BattleCity::onCharacterChosen);
    dialog->exec();
}



