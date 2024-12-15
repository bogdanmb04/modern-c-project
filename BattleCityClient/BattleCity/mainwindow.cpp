#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include "ClickableLabel.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

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

    loadMapFromServer();
    initializeMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadMapFromServer()
{
    // Se trimite cererea GET cãtre server
    httpManager.sendGetRequest("http://localhost:18080/map", [this](const cpr::Response& response) {
        if (response.status_code == 200) {
            QJsonDocument doc = QJsonDocument::fromJson(response.text.c_str());

            // Verificãm dacã documentul JSON este valid
            if (doc.isNull() || !doc.isObject()) {
                QMessageBox::warning(this, "Eroare", "Datele hartii sunt invalide.");
                return;
            }

            QJsonObject jsonResponse = doc.object();

            // Verificãm dacã JSON-ul con?ine câmpurile necesare
            if (!jsonResponse.contains("data") || !jsonResponse.contains("width") || !jsonResponse.contains("height")) {
                QMessageBox::warning(this, "Eroare", "Datele hartii sunt incomplete.");
                return;
            }

            int width = jsonResponse["width"].toInt();
            int height = jsonResponse["height"].toInt();
            QJsonArray dataArray = jsonResponse["data"].toArray();

            qDebug() << "Width: " << width;
            qDebug() << "Height: " << height;
            qDebug() << "Data Array Size: " << dataArray.size();

            mapData.clear();
            int rowIndex = 0;
            QVector<int> currentRow;

            // Parcurgem datele
            for (const QJsonValue& value : dataArray) {
                if (value.isObject()) {
                    QJsonObject obj = value.toObject();
                    if (obj.contains("type")) {
                        currentRow.append(obj["type"].toInt());
                    }
                }

                // Dacã ajungem la sfâr?itul unui rând, adãugãm rândul în mapData
                if (currentRow.size() == width) {
                    mapData.append(currentRow);
                    currentRow.clear();
                }
                rowIndex++;
            }

            // Verificãm dacã dimensiunile sunt corecte
            if (mapData.isEmpty() || mapData.size() != height) {
                QMessageBox::warning(this, "Eroare", "Harta are dimensiuni invalide.");
                mapData.clear();
                return;
            }

            // Asigurãm cã toate liniile au aceea?i lungime
            for (auto& row : mapData) {
                while (row.size() < width) {
                    row.append(0);  // Adãugãm 0 pentru a completa rândul
                }
            }

            // Verificãm dacã harta este completã
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
    // ?tergem orice widget existent pe gridLayout
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

    // Parcurgem harta pentru a crea celulele
    for (int row = 0; row < mapData.size(); ++row) {
        for (int col = 0; col < mapData[row].size(); ++col) {
            ClickableLabel* cell = new ClickableLabel(this);
            cell->setFixedSize(cellSize, cellSize);
            cell->setCoordinates(row, col);

            QString style;
            switch (mapData[row][col]) {
            case 1:
                style = "background-color: brown; border: 0px; margin: 0px; padding: 0px;";
                break;
            case 2:
                style = "background-color: red; border: 0px; margin: 0px; padding: 0px;";
                break;
            case 0:
                style = "background-color: black; border: 0px; margin: 0px; padding: 0px;";
                break;
            case 3:
                style = "background-color: green; border: 0px; margin: 0px; padding: 0px;";
                break;
            }

            // Stil special pentru colturile bazei
            if ((row == 1 && col == 1) || (row == 1 && col == mapData[row].size() - 2) ||
                (row == mapData.size() - 2 && col == 1) || (row == mapData.size() - 2 && col == mapData[row].size() - 2)) {
                style = "background-color: white; border-radius: 5px; border: 0px; margin: 0px; padding: 0px;";
            }

            cell->setStyleSheet(style);

            // Conectãm click-ul celulei
            connect(cell, &ClickableLabel::clicked, this, &MainWindow::onCellClicked);

            gridLayout->addWidget(cell, row, col);
        }
    }

    // For?ãm actualizarea layout-ului
    gridLayout->update();
    this->update();
}

void MainWindow::onCellClicked(int row, int col)
{
    if (mapData[row][col] == 1) {
        // Zid destructibil
        mapData[row][col] = 0;

        QWidget* widget = gridLayout->itemAtPosition(row, col)->widget();
        QLabel* cell = qobject_cast<QLabel*>(widget);

        if (cell) {
            cell->setStyleSheet("background-color: black; border: 0px;");
        }
    }
    else if (mapData[row][col] == 2) {
        // Zid indestructibil
        QMessageBox::information(this, "Info", "Acest perete este indestructibil!");
    }
}
