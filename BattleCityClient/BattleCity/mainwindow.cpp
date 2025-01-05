#include "mainwindow.h"
#include "battlecitystart.h"
#include "ui_mainwindow.h"
#include "ClickableLabel.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QTimer>
#include <cstdlib>
#include <ctime>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gridLayout(new QGridLayout())
    , httpManager()
{
    ui->setupUi(this);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);

    QPushButton* menuButton = new QPushButton("Menu", this);
    menuButton->setStyleSheet("font-size: 10px; padding: 10px;");
    menuButton->setFixedSize(70, 40);
    QVBoxLayout* backLayout = new QVBoxLayout();
    backLayout->addWidget(menuButton);
    backLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    QPixmap backPixmap(":/BattleCity/images/Back.png");
    menuButton->setIcon(QIcon(backPixmap));
    menuButton->setIconSize(QSize(10, 10));
    menuButton->setText("Menu");
    centralWidget->setLayout(backLayout);

    connect(menuButton, &QPushButton::clicked, this, &MainWindow::BackButtonClicked);

    loadMapFromServer();
    initializeMap();

    coinTimer = new QTimer(this);
    connect(coinTimer, &QTimer::timeout, this, &MainWindow::placeCoins);
    coinTimer->start(60000);

    objectSpawnTimer = new QTimer(this);
    connect(objectSpawnTimer, &QTimer::timeout, this, &MainWindow::spawnRandomObjects);
    objectSpawnTimer->start(120000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::BackButtonClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmare", "Are you sure you want to quit?",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit backToBattleCity();
        this->close();
    }
}

void MainWindow::loadMapFromServer()
{
    httpManager.sendGetRequest("http://localhost:18080/map", [this](const cpr::Response& response) {
        if (response.status_code == 200) {
            QJsonDocument doc = QJsonDocument::fromJson(response.text.c_str());

            if (doc.isNull() || !doc.isObject()) {
                QMessageBox::warning(this, "Eroare", "Datele hartii sunt invalide.");
                return;
            }

            QJsonObject jsonResponse = doc.object();

            if (!jsonResponse.contains("width") || !jsonResponse.contains("height") || !jsonResponse.contains("layout")) {
                QMessageBox::warning(this, "Eroare", "Datele hartii sunt incomplete.");
                return;
            }

            int width = jsonResponse["width"].toInt();
            int height = jsonResponse["height"].toInt();
            QJsonArray layout = jsonResponse["layout"].toArray();

            mapData.clear();
            int rowIndex = 0;
            QVector<int> currentRow;

            for (const QJsonValue& value : layout) {
                if (value.isObject()) {
                    QJsonObject obj = value.toObject();
                    if (obj.contains("type")) {
                        currentRow.append(obj["type"].toInt());
                    }
                }

                if (currentRow.size() == width) {
                    mapData.append(currentRow);
                    currentRow.clear();
                }
                rowIndex++;
            }

            if (mapData.isEmpty() || mapData.size() != height) {
                QMessageBox::warning(this, "Eroare", "Harta are dimensiuni invalide.");
                mapData.clear();
                return;
            }

            for (auto& row : mapData) {
                while (row.size() < width) {
                    row.append(0);
                }
            }

            initializeMap();
        }
        else {
            QMessageBox::warning(this, "Eroare", "Nu s-a putut obtine harta de la server.");
        }
        });
}

void MainWindow::initializeMap()
{
    while (QLayoutItem* item = gridLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    if (mapData.isEmpty()) return;

    int cellWidth = this->width() / mapData[0].size();
    int cellHeight = this->height() / mapData.size();
    int cellSize = qMin(cellWidth, cellHeight);

    for (int row = 0; row < mapData.size(); ++row) {
        for (int col = 0; col < mapData[row].size(); ++col) {
            ClickableLabel* cell = new ClickableLabel(this);
            cell->setFixedSize(cellSize, cellSize);
            cell->setCoordinates(row, col);

            QString imagePath;
            switch (mapData[row][col]) {
            case 1:
                imagePath = ":/BattleCity/images/BreakableWall_Type1.png";
                break;
            case 2:
                imagePath = ":/BattleCity/images/UnbreakableWall_Type1.png";
                break;
            case 0:
                imagePath = ":/BattleCity/images/Path.png";
                break;
            case 3:
                imagePath = ":/BattleCity/images/Bomb.png";
                break;
            default:
                imagePath = ":/BattleCity/images/Path.png";
                break;
            }

            QString style = QString("background-image: url(%1); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;")
                .arg(imagePath);
            if ((row == 1 && col == 1) || (row == 1 && col == mapData[row].size() - 2) ||
                (row == mapData.size() - 2 && col == 1) || (row == mapData.size() - 2 && col == mapData[row].size() - 2)) {
                style = "background-color: white; border-radius: 5px; border: 0px; margin: 0px; padding: 0px;";
            }

            cell->setStyleSheet(style);
            connect(cell, &ClickableLabel::clicked, this, &MainWindow::onCellClicked);

            gridLayout->addWidget(cell, row, col);
        }
    }

    gridLayout->update();
    this->update();
}

void MainWindow::placeCoins()
{
    int coinsToPlace = QRandomGenerator::global()->bounded(1, 6);
    for (int i = 0; i < coinsToPlace; ++i) {
        if (!placeCoinAtRandomLocation()) {
            break;
        }
    }
}

void MainWindow::onCellClicked(int row, int col)
{
    if (mapData[row][col] == 1) {
        mapData[row][col] = 3;

        QWidget* widget = gridLayout->itemAtPosition(row, col)->widget();
        QLabel* cell = qobject_cast<QLabel*>(widget);

        if (cell) {
            QString style = "background-image: url(:/BattleCity/images/Bomb.png); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;";
            cell->setStyleSheet(style);
        }

        QTimer::singleShot(500, [this, row, col]() {
            triggerExplosion(row, col);
            });
    }
    else if (mapData[row][col] == 3) {
        triggerExplosion(row, col);
    }
}

void MainWindow::triggerExplosion(int row, int col)
{
    const int explosionRadius = 3;

    if (mapData[row][col] == 1) {
        mapData[row][col] = 0;
        QWidget* widget = gridLayout->itemAtPosition(row, col)->widget();
        QLabel* cell = qobject_cast<QLabel*>(widget);

        if (cell) {
            QString style = "background-image: url(:/BattleCity/images/Path.png); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;";
            cell->setStyleSheet(style);
        }
    }

    placeRandomBombsAround(row, col);

    QTimer::singleShot(200, [this, row, col]() {
        for (int i = -explosionRadius; i <= explosionRadius; ++i) {
            for (int j = -explosionRadius; j <= explosionRadius; ++j) {
                if (row + i >= 0 && row + i < mapData.size() && col + j >= 0 && col + j < mapData[0].size()) {
                    if (mapData[row + i][col + j] == 1) {
                        mapData[row + i][col + j] = 0;
                        QWidget* widget = gridLayout->itemAtPosition(row + i, col + j)->widget();
                        QLabel* cell = qobject_cast<QLabel*>(widget);

                        if (cell) {
                            QString style = "background-image: url(:/BattleCity/images/Path.png); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;";
                            cell->setStyleSheet(style);
                        }
                    }
                }
            }
        }
        });
}

void MainWindow::placeRandomBombsAround(int row, int col)
{
    int rowOffset[] = { -1, 1, 0, 0 };
    int colOffset[] = { 0, 0, -1, 1 };
    for (int i = 0; i < 4; ++i) {
        int newRow = row + rowOffset[i];
        int newCol = col + colOffset[i];
        if (newRow >= 0 && newRow < mapData.size() && newCol >= 0 && newCol < mapData[0].size() &&
            mapData[newRow][newCol] == 0) {
            mapData[newRow][newCol] = 3;

            QWidget* widget = gridLayout->itemAtPosition(newRow, newCol)->widget();
            QLabel* cell = qobject_cast<QLabel*>(widget);
            if (cell) {
                QString style = "background-image: url(:/BattleCity/images/Bomb.png); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;";
                cell->setStyleSheet(style);
            }
        }
    }
}

void MainWindow::spawnRandomObjects()
{
    static QRandomGenerator generator;

    const QStringList objectTypes = {
        ":/BattleCity/images/Beer.png",
        ":/BattleCity/images/Invisible.png",
        ":/BattleCity/images/BombBall_Type1.png",
        ":/BattleCity/images/Bomb.png",
        ":/BattleCity/images/Powerup.png"
    };

    for (int i = 0; i < 3; ++i) {
        int row = generator.bounded(mapData.size());
        int col = generator.bounded(mapData[row].size());

        if (mapData[row][col] == 0) {
            mapData[row][col] = 4 + i;

            QWidget* widget = gridLayout->itemAtPosition(row, col)->widget();
            QLabel* cell = qobject_cast<QLabel*>(widget);
            if (cell) {
                QString style = QString("background-image: url(%1); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;")
                    .arg(objectTypes[i]);
                cell->setStyleSheet(style);
            }
        }
    }
}

bool MainWindow::placeCoinAtRandomLocation()
{
  
    QVector<QPair<int, int>> emptyCells;
    for (int row = 0; row < mapData.size(); ++row) {
        for (int col = 0; col < mapData[row].size(); ++col) {
            if (mapData[row][col] == 0) { 
                emptyCells.append(qMakePair(row, col));
            }
        }
    }

    if (emptyCells.isEmpty()) {
        return false;
    }

   
    QPair<int, int> randomCell = emptyCells[QRandomGenerator::global()->bounded(emptyCells.size())];
    int row = randomCell.first;
    int col = randomCell.second;

  
    mapData[row][col] = 4; 

  
    QWidget* widget = gridLayout->itemAtPosition(row, col)->widget();
    QLabel* cell = qobject_cast<QLabel*>(widget);

    if (cell) {
        QString style = "background-image: url(:/BattleCity/images/Coin.png); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;";
        cell->setStyleSheet(style);
    }

    return true;
}