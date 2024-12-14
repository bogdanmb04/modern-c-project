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
    gridLayout->setSpacing(0); // Fara spatii intre celule
    gridLayout->setContentsMargins(0, 0, 0, 0); // Fara margini
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);

    // Incarcarea hartii si initializarea grilei
    loadMapFromServer();
    initializeMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadMapFromServer()
{
    httpManager.sendGetRequest("http://localhost:18080/map", [this](const cpr::Response& response) {
        if (response.status_code == 200) {
            QJsonDocument doc = QJsonDocument::fromJson(response.text.c_str());
            if (doc.isNull() || !doc.isArray()) {
                QMessageBox::warning(this, "Eroare", "Datele hartii sunt invalide.");
                return;
            }

            QJsonArray jsonResponse = doc.array();
            mapData.clear();

            QVector<int> currentRow;
            int maxColumns = 0;

            for (int i = 0; i < jsonResponse.size(); i++) {
                const QJsonValue& value = jsonResponse[i];
                if (value.isObject()) {
                    QJsonObject obj = value.toObject();
                    if (obj.contains("type")) {
                        int type = obj["type"].toInt();
                        currentRow.append(type);
                    }
                }

                //TODO: We also need the map dimensions
                if (currentRow.size() == 10) {
                    mapData.append(currentRow);
                    maxColumns = qMax(maxColumns, currentRow.size());
                    currentRow.clear();
                }
            }

            if (!currentRow.isEmpty()) {
                mapData.append(currentRow);
                maxColumns = qMax(maxColumns, currentRow.size());
            }

            for (auto& row : mapData) {
                while (row.size() < maxColumns) {
                    row.append(0);
                }
            }
            int rowSize = mapData.isEmpty() ? 0 : mapData[0].size();
            for (const QVector<int>& row : mapData) {
                if (row.size() != rowSize) {
                    QMessageBox::warning(this, "Eroare", "Harta contine randuri de dimensiuni inegale.");
                    mapData.clear();
                    return;
                }
            }
            if (mapData.isEmpty()) {
                QMessageBox::warning(this, "Eroare", "Harta este goala sau nu contine date valide.");
                return;
            }
        }
        else {
            QMessageBox::warning(this, "Eroare", "Nu s-a putut obtine harta de la server.");
        }
        });
}


void MainWindow::initializeMap()
{
    // Eliminam orice widget anterior din layout
    while (QLayoutItem* item = gridLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    // Eliminam marginile si spatiile dintre widget-uri
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    if (mapData.isEmpty()) return;

    // Calculam dimensiunile celulelor pentru a umple complet fereastra
    int cellWidth = this->width() / mapData[0].size();
    int cellHeight = this->height() / mapData.size();
    int cellSize = qMin(cellWidth, cellHeight);

    for (int row = 0; row < mapData.size(); ++row) {
        for (int col = 0; col < mapData[row].size(); ++col) {
            ClickableLabel* cell = new ClickableLabel(this);
            cell->setFixedSize(cellSize, cellSize);
            cell->setCoordinates(row, col);

            // Stiluri personalizate pentru celule
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
            default:
                style = "background-color: green; border: 0px; margin: 0px; padding: 0px;";
                break;
            }

            // Stil special pentru colturile bazei
            if ((row == 1 && col == 1) || (row == 1 && col == mapData[row].size() - 2) ||
                (row == mapData.size() - 2 && col == 1) || (row == mapData.size() - 2 && col == mapData[row].size() - 2)) {
                style = "background-color: white; border-radius: 5px; border: 0px; margin: 0px; padding: 0px;";
            }

            cell->setStyleSheet(style);

            // Conectam click-ul celulei
            connect(cell, &ClickableLabel::clicked, this, &MainWindow::onCellClicked);

            gridLayout->addWidget(cell, row, col);
        }
    }

    // Fortam actualizarea layout-ului
    gridLayout->update();
    this->update();
}

// Adaugam metoda resizeEvent pentru a recalcula dimensiunile la redimensionare
/*void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event); // Apelam metoda parintelui
    initializeMap(); // Recalculeaza dimensiunile si redeseneaza celulele
}*/

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
