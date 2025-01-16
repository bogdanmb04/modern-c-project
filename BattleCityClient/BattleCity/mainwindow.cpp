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
#include <nlohmann/json.hpp>
#include <QtWidgets>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , userId(0)
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

    //centralWidget->setStyleSheet("background-color: #2b2b2b;");

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


void MainWindow::onLoginSuccess(uint32_t userId)
{
    this->userId = userId;
    loadMapFromServer();
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

            int expectedLayoutSize = width * height;

            mapData.clear();
            QVector<int> currentRow;

            for (int i = 0; i < layout.size(); ++i) {
                const QJsonValue& value = layout[i];
                if (value.isObject()) {
                    QJsonObject obj = value.toObject();
                    int tile = obj["tile"].toInt();
                    int direction = obj["direction"].toInt();
                    QString entity = obj["entity"].toString();

                    currentRow.append(tile);

                    if (currentRow.size() == width) {
                        mapData.append(currentRow);
                        currentRow.clear();
                    }
                }
            }

            initializeMap();
        }
        else {
            QMessageBox::warning(this, "Error", "The map couldn't be loaded from server.");
        }
        });


}

void MainWindow::initializeMap()
{
    while (QLayoutItem* item = gridLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    if (mapData.isEmpty()) return;

    int cellWidth = this->width();
    int cellHeight = this->height();
    int cellSize = qMin(cellWidth, cellHeight);

    int windowWidth = cellSize * mapData[0].size();
    int windowHeight = cellSize * mapData.size();
    this->resize(windowWidth, windowHeight);

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
                imagePath = ":/BattleCity/images/Path2.png";
                break;
            }

            QString style = QString("background-image: url(%1); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;")
                .arg(imagePath);

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
    const int explosionRadius = 5;

    if (mapData[row][col] == 1) {
        mapData[row][col] = 0;
        QWidget* widget = gridLayout->itemAtPosition(row, col)->widget();
        QLabel* cell = qobject_cast<QLabel*>(widget);

        if (cell) {
            QString style = "background-image: url(:/BattleCity/images/Path2.png); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;";
            cell->setStyleSheet(style);
        }
    }

    QTimer::singleShot(200, [this, row, col]() {
        for (int i = -explosionRadius; i <= explosionRadius; ++i) {
            for (int j = -explosionRadius; j <= explosionRadius; ++j) {
                if (row + i >= 0 && row + i < mapData.size() && col + j >= 0 && col + j < mapData[0].size()) {
                    if (mapData[row + i][col + j] == 1) {
                        mapData[row + i][col + j] = 0;
                        QWidget* widget = gridLayout->itemAtPosition(row + i, col + j)->widget();
                        QLabel* cell = qobject_cast<QLabel*>(widget);

                        if (cell) {
                            QString style = "background-image: url(:/BattleCity/images/Path2.png); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;";
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

        if (mapData[row][col] == 1) {
    mapData[row][col] = 0;
    QWidget* widget = gridLayout->itemAtPosition(row, col)->widget();
    QLabel* cell = qobject_cast<QLabel*>(widget);

    if (cell) {
        QString style = "background-image: url(:/BattleCity/images/Path2.png); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;";
        cell->setStyleSheet(style);
    }
}

    }

}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_W:
        playerDirection = Direction::Up;
        break;
    case Qt::Key_S:
        playerDirection = Direction::Down;
        break;
    case Qt::Key_A:
        playerDirection = Direction::Left;
        break;
    case Qt::Key_D:
        playerDirection = Direction::Right;
        break;
    default:
        return;
    }
    movePlayer(userId, playerDirection);
}


void MainWindow::movePlayer(uint32_t playerID, Direction direction) {
    QString directionStr;
    switch (direction) {
    case Direction::Up: directionStr = "Up"; break;
    case Direction::Down: directionStr = "Down"; break;
    case Direction::Left: directionStr = "Left"; break;
    case Direction::Right: directionStr = "Right"; break;
    }

    QJsonObject moveData;
    moveData["playerID"] = static_cast<int>(userId);
    moveData["direction"] = directionStr;

    QJsonDocument doc(moveData);
    QString moveDataStr = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));


    httpManager.sendPostRequest("http://localhost:18080/move", moveDataStr, [this](const cpr::Response& response) {
        if (response.status_code == 200) {
            try {
                auto jsonResponse = nlohmann::json::parse(response.text);
                if (jsonResponse.contains("status") && jsonResponse["status"] == "Move successful") {
                    QMessageBox::warning(this, "Eroare", "Player moved successfully!");
                }
                else {
                    QMessageBox::warning(this, "Eroare", "Invalid response format!");
                }
            }
            catch (const std::exception& e) {
                QMessageBox::warning(this, "Eroare", "Error parsing the server response");
            }
        }
        else {
            QMessageBox::warning(this, "Eroare", "Server error");
        }
        });
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
