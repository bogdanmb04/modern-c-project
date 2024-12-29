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

    QPushButton* backButton = new QPushButton("Back", this);
    backButton->setStyleSheet("font-size: 10px; padding: 10px;");
    backButton->setFixedSize(70, 40);
    QVBoxLayout* backLayout = new QVBoxLayout();
    backLayout->addWidget(backButton);
    backLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    QPixmap backPixmap(":/BattleCity/images/Back.png");
    backButton->setIcon(QIcon(backPixmap));
    backButton->setIconSize(QSize(10, 10));
    backButton->setText("Back");
    centralWidget->setLayout(backLayout);

    connect(backButton, &QPushButton::clicked, this, &MainWindow::BackButtonClicked);

    loadMapFromServer();
    initializeMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::BackButtonClicked()
{
  
    emit backToBattleCity();
    this->close(); 
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
            QJsonArray layoutArray = jsonResponse["layout"].toArray();

            qDebug() << "Width: " << width;
            qDebug() << "Height: " << height;
            qDebug() << "Layout Array Size: " << layoutArray.size();

            mapData.clear();
            int rowIndex = 0;
            QVector<int> currentRow;

            for (const QJsonValue& value : layoutArray) {
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

            qDebug() << "Map Data Size: " << mapData.size() << "x" << (mapData.isEmpty() ? 0 : mapData[0].size());
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


void MainWindow::keyPressEvent(QKeyEvent* event)
{
    int playerID = 1;
    QString direction;

    switch (event->key()) {
    case Qt::Key_W:
        direction = "up";
        break;
    case Qt::Key_A:
        direction = "left";
        break;
    case Qt::Key_S:
        direction = "down";
        break;
    case Qt::Key_D:
        direction = "right";
        break;
    default:
        QMainWindow::keyPressEvent(event);
        return;
    }

    sendMoveRequest(playerID, direction);
    QMainWindow::keyPressEvent(event);
}

void MainWindow::sendMoveRequest(int playerID, const QString& direction)
{
    QJsonObject jsonData;
    jsonData["playerID"] = playerID;
    jsonData["direction"] = direction;

    QJsonDocument doc(jsonData);
    QByteArray data = doc.toJson();

    httpManager.sendPostRequest("http://localhost:18080/move", data, [this](const cpr::Response& response) {
        if (response.status_code == 200) {
            QMessageBox::information(this, "Success", "Move successful!");
        }
        else {
            QMessageBox::critical(this, "Error", "Failed to move the player.");
        }
        });
}

void MainWindow::triggerExplosion(int row, int col)
{
    const int explosionRadius = 10;

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
                int targetRow = row + i;
                int targetCol = col + j;

                if (targetRow >= 0 && targetRow < mapData.size() &&
                    targetCol >= 0 && targetCol < mapData[0].size()) {

                    if (mapData[targetRow][targetCol] == 1) {
                        mapData[targetRow][targetCol] = 0;
                        QWidget* widget = gridLayout->itemAtPosition(targetRow, targetCol)->widget();
                        QLabel* cell = qobject_cast<QLabel*>(widget);

                        if (cell) {
                            QString style = "background-image: url(:/BattleCity/images/Path.png); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;";
                            cell->setStyleSheet(style);
                        }
                    }
                    else if (mapData[targetRow][targetCol] == 3) {
                        triggerExplosion(targetRow, targetCol);
                    }
                }
            }
        }

        mapData[row][col] = 0;
        QWidget* widget = gridLayout->itemAtPosition(row, col)->widget();
        QLabel* cell = qobject_cast<QLabel*>(widget);

        if (cell) {
            QString style = "background-image: url(:/BattleCity/images/Path.png); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;";
            cell->setStyleSheet(style);
        }
        });
}

void MainWindow::placeRandomBombsAround(int row, int col)
{
    QVector<QPair<int, int>> neighbors;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newRow = row + i;
            int newCol = col + j;

            if (newRow >= 0 && newRow < mapData.size() &&
                newCol >= 0 && newCol < mapData[0].size() &&
                mapData[newRow][newCol] == 1) {
                neighbors.append(qMakePair(newRow, newCol));
            }
        }
    }

    if (!neighbors.isEmpty()) {
        QPair<int, int> randomNeighbor = neighbors[QRandomGenerator::global()->bounded(neighbors.size())];
        int bombRow = randomNeighbor.first;
        int bombCol = randomNeighbor.second;

        mapData[bombRow][bombCol] = 3;

        QWidget* widget = gridLayout->itemAtPosition(bombRow, bombCol)->widget();
        QLabel* cell = qobject_cast<QLabel*>(widget);
        if (cell) {
            QString style = "background-image: url(:/BattleCity/images/Bomb.png); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;";
            cell->setStyleSheet(style);
        }

        QTimer::singleShot(100, [this, bombRow, bombCol]() {
            mapData[bombRow][bombCol] = 0;
            QWidget* widget = gridLayout->itemAtPosition(bombRow, bombCol)->widget();
            QLabel* cell = qobject_cast<QLabel*>(widget);
            if (cell) {
                QString style = "background-image: url(:/BattleCity/images/Path.png); background-repeat: no-repeat; background-size: cover; border: 0px; margin: 0px; padding: 0px;";
                cell->setStyleSheet(style);
            }
            });
    }
}