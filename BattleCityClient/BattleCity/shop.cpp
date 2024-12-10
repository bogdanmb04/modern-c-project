#include "shop.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

Shop::Shop(QWidget* parent) : QWidget(parent) {
    setupUI();
}

Shop::~Shop() {}

void Shop::setupUI() {

    setWindowTitle("Shop");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(10);

    QSpacerItem* spacerAboveTitle = new QSpacerItem(60, 60, QSizePolicy::Minimum, QSizePolicy::Fixed); // Înãl?ime 20px
    mainLayout->addSpacerItem(spacerAboveTitle);

    QLabel* titleLabel = new QLabel("Shop", this);
    titleLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    titleLabel->setStyleSheet("font-size: 50px; font-weight: bold; margin-bottom: 20px;");
    mainLayout->addWidget(titleLabel);

  

    QHBoxLayout* buttonsLayout = new QHBoxLayout();

    QVBoxLayout* leftColumn = new QVBoxLayout();
    QPushButton* button1 = new QPushButton("Upgrade 1", this);
    QPushButton* button2 = new QPushButton("Upgrade 2", this);
    QPushButton* button3 = new QPushButton("Upgrade 3", this);

    button1->setFixedSize(700, 170); 
    button2->setFixedSize(700, 170);
    button3->setFixedSize(700, 170);

    leftColumn->addWidget(button1);
    leftColumn->addWidget(button2);
    leftColumn->addWidget(button3);

    QVBoxLayout* rightColumn = new QVBoxLayout();
    QPushButton* button4 = new QPushButton("Upgrade 4", this);
    QPushButton* button5 = new QPushButton("Upgrade 5", this);
    QPushButton* button6 = new QPushButton("Upgrade 6", this);

    button4->setFixedSize(700, 170);
    button5->setFixedSize(700, 170);
    button6->setFixedSize(700, 170);

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
