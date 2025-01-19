#include "CharacterSelection.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include "resources.h"

CharacterSelection::CharacterSelection(QWidget* parent)
    : QDialog(parent) {
    setupUI();
}

void CharacterSelection::setupUI() {
    this->setWindowState(Qt::WindowMaximized);
    this->setStyleSheet("background-color: #022423;");
    QHBoxLayout* layout = new QHBoxLayout(this);

    QVBoxLayout* leftLayout = new QVBoxLayout();

    QLabel* policeOfficerLabel = new QLabel("Police Officer");
    policeOfficerLabel->setAlignment(Qt::AlignCenter);
    policeOfficerLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    QHBoxLayout* firstRowLayout = new QHBoxLayout();
    QVBoxLayout* firstOfficerLayout = new QVBoxLayout();

    QLabel* policeOfficerImage1 = new QLabel();
    QPixmap policeOfficerPixmap1(Constants::kPoliceOfficer);
    policeOfficerImage1->setPixmap(policeOfficerPixmap1.scaled(230, 230, Qt::KeepAspectRatio));
    policeOfficerImage1->setAlignment(Qt::AlignCenter);
    QPushButton* policeOfficerButton1 = new QPushButton("Choose Blue Police Officer ");
    connect(policeOfficerButton1, &QPushButton::clicked, this, &CharacterSelection::choosePoliceOfficer1);

    firstOfficerLayout->addWidget(policeOfficerImage1);
    firstOfficerLayout->addWidget(policeOfficerButton1);

    QVBoxLayout* secondOfficerLayout = new QVBoxLayout();

    QLabel* policeOfficerImage2 = new QLabel();
    QPixmap policeOfficerPixmap2(Constants::kPoliceOfficer2);
    policeOfficerImage2->setPixmap(policeOfficerPixmap2.scaled(230, 230, Qt::KeepAspectRatio));
    policeOfficerImage2->setAlignment(Qt::AlignCenter);
    QPushButton* policeOfficerButton2 = new QPushButton("Choose Purple Police Officer");
    connect(policeOfficerButton2, &QPushButton::clicked, this, &CharacterSelection::choosePoliceOfficer2);

    secondOfficerLayout->addWidget(policeOfficerImage2);
    secondOfficerLayout->addWidget(policeOfficerButton2);

    firstRowLayout->addLayout(firstOfficerLayout);
    firstRowLayout->addLayout(secondOfficerLayout);

    QHBoxLayout* secondRowLayout = new QHBoxLayout();
    QVBoxLayout* thirdOfficerLayout = new QVBoxLayout();

    QLabel* policeOfficerImage3 = new QLabel();
    QPixmap policeOfficerPixmap3(Constants::kPoliceOfficer3);
    policeOfficerImage3->setPixmap(policeOfficerPixmap3.scaled(230, 230, Qt::KeepAspectRatio));
    policeOfficerImage3->setAlignment(Qt::AlignCenter);
    QPushButton* policeOfficerButton3 = new QPushButton("Choose Green Police Officer");
    connect(policeOfficerButton3, &QPushButton::clicked, this, &CharacterSelection::choosePoliceOfficer3);

    thirdOfficerLayout->addWidget(policeOfficerImage3);
    thirdOfficerLayout->addWidget(policeOfficerButton3);

    QVBoxLayout* fourthOfficerLayout = new QVBoxLayout();

    QLabel* policeOfficerImage4 = new QLabel();
    QPixmap policeOfficerPixmap4(Constants::kPoliceOfficer4);
    policeOfficerImage4->setPixmap(policeOfficerPixmap4.scaled(230, 230, Qt::KeepAspectRatio));
    policeOfficerImage4->setAlignment(Qt::AlignCenter);
    QPushButton* policeOfficerButton4 = new QPushButton("Choose Yellow Police Officer");
    connect(policeOfficerButton4, &QPushButton::clicked, this, &CharacterSelection::choosePoliceOfficer4);

    fourthOfficerLayout->addWidget(policeOfficerImage4);
    fourthOfficerLayout->addWidget(policeOfficerButton4);

    secondRowLayout->addLayout(thirdOfficerLayout);
    secondRowLayout->addLayout(fourthOfficerLayout);

    leftLayout->addWidget(policeOfficerLabel);
    leftLayout->addLayout(firstRowLayout);
    leftLayout->addLayout(secondRowLayout);


    QVBoxLayout* rightLayout = new QVBoxLayout();

    QLabel* zombieLabel = new QLabel("Zombie");
    zombieLabel->setAlignment(Qt::AlignCenter);
    zombieLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    
    QHBoxLayout* firstZombieRowLayout = new QHBoxLayout();
    QVBoxLayout* firstZombieLayout = new QVBoxLayout();
    QLabel* zombieImage1 = new QLabel();
    QPixmap zombiePixmap1(Constants::kZombie);
    zombieImage1->setPixmap(zombiePixmap1.scaled(230, 230, Qt::KeepAspectRatio));
    zombieImage1->setAlignment(Qt::AlignCenter);
    QPushButton* zombieButton1 = new QPushButton("Choose Purple Zombie");
    connect(zombieButton1, &QPushButton::clicked, this, &CharacterSelection::chooseZombieType1);

    firstZombieLayout->addWidget(zombieImage1);
    firstZombieLayout->addWidget(zombieButton1);

    QVBoxLayout* secondZombieLayout = new QVBoxLayout();
    QLabel* zombieImage2 = new QLabel();
    QPixmap zombiePixmap2(Constants::kZombie1);
    zombieImage2->setPixmap(zombiePixmap2.scaled(230, 230, Qt::KeepAspectRatio));
    zombieImage2->setAlignment(Qt::AlignCenter);
    QPushButton* zombieButton2 = new QPushButton("Choose Green Zombie ");
    connect(zombieButton2, &QPushButton::clicked, this, &CharacterSelection::chooseZombieType2);

    secondZombieLayout->addWidget(zombieImage2);
    secondZombieLayout->addWidget(zombieButton2);

    firstZombieRowLayout->addLayout(firstZombieLayout);
    firstZombieRowLayout->addLayout(secondZombieLayout);

    QHBoxLayout* secondZombieRowLayout = new QHBoxLayout();
    QVBoxLayout* thirdZombieLayout = new QVBoxLayout();
    QLabel* zombieImage3 = new QLabel();
    QPixmap zombiePixmap3(Constants::kZombie2);
    zombieImage3->setPixmap(zombiePixmap3.scaled(230, 230, Qt::KeepAspectRatio));
    zombieImage3->setAlignment(Qt::AlignCenter);
    QPushButton* zombieButton3 = new QPushButton("Choose Yellow Zombie ");
    connect(zombieButton3, &QPushButton::clicked, this, &CharacterSelection::chooseZombieType3);

    thirdZombieLayout->addWidget(zombieImage3);
    thirdZombieLayout->addWidget(zombieButton3);

    QVBoxLayout* fourthZombieLayout = new QVBoxLayout();
    QLabel* zombieImage4 = new QLabel();
    QPixmap zombiePixmap4(Constants::kZombie3);
    zombieImage4->setPixmap(zombiePixmap4.scaled(230, 230, Qt::KeepAspectRatio));
    zombieImage4->setAlignment(Qt::AlignCenter);
    QPushButton* zombieButton4 = new QPushButton("Choose Zombie Type 4");
    connect(zombieButton4, &QPushButton::clicked, this, &CharacterSelection::chooseZombieType4);

    fourthZombieLayout->addWidget(zombieImage4);
    fourthZombieLayout->addWidget(zombieButton4);

    secondZombieRowLayout->addLayout(thirdZombieLayout);
    secondZombieRowLayout->addLayout(fourthZombieLayout);

    rightLayout->addWidget(zombieLabel);
    rightLayout->addLayout(firstZombieRowLayout);
    rightLayout->addLayout(secondZombieRowLayout);

    layout->addLayout(leftLayout);
    layout->addLayout(rightLayout);

    this->setLayout(layout);
}


void CharacterSelection::choosePoliceOfficer1() {
    emit characterChosen("PoliceOfficer1");
    close();
}

void CharacterSelection::choosePoliceOfficer2() {
    emit characterChosen("PoliceOfficer2");
    close();
}

void CharacterSelection::choosePoliceOfficer3() {
    emit characterChosen("PoliceOfficer3");
    close();
}

void CharacterSelection::choosePoliceOfficer4() {
    emit characterChosen("PoliceOfficer4");
    close();
}

void CharacterSelection::chooseZombieType1() {
    emit characterChosen("Zombie_Type1");
    close();
}

void CharacterSelection::chooseZombieType2() {
    emit characterChosen("Zombie_Type2");
    close();
}

void CharacterSelection::chooseZombieType3() {
    emit characterChosen("Zombie_Type3");
    close();
}

void CharacterSelection::chooseZombieType4() {
    emit characterChosen("Zombie_Type4");
    close();
}