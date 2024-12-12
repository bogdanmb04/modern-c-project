#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include "ClickableLabel.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gridLayout(new QGridLayout())
{
    ui->setupUi(this);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
    gridLayout->setSpacing(0); // F�r� spa?ii �ntre celule
    gridLayout->setContentsMargins(0, 0, 0, 0); // F�r� margini
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);

    // �nc�rcarea h�r?ii ?i ini?ializarea grilei
    loadMapFromFile("map.txt");
    initializeMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadMapFromFile(const QString& filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Eroare", "Nu s-a putut deschide fi?ierul: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    mapData.clear();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QVector<int> rowData;

        for (QChar ch : line) {
            if (ch == '0') rowData.append(0);
            else if (ch == '1') rowData.append(1);
            else if (ch == '2') rowData.append(2);
            else if (ch == '3') rowData.append(3);
        }

        if (!rowData.isEmpty()) {
            mapData.append(rowData);
        }
    }

    file.close();

    if (mapData.isEmpty()) {
        QMessageBox::warning(this, "Eroare", "Fi?ierul este gol sau nu con?ine date valide.");
        return;
    }

    // Verificare pentru dimensiuni consistente ale r�ndurilor
    int rowSize = mapData[0].size();
    for (const QVector<int>& row : mapData) {
        if (row.size() != rowSize) {
            QMessageBox::warning(this, "Eroare", "Fi?ierul de hart� are r�nduri de dimensiuni inegale.");
            mapData.clear();
            return;
        }
    }
}

void MainWindow::initializeMap()
{
    // Elimin�m orice widget anterior din layout
    while (QLayoutItem* item = gridLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    // Elimin�m marginile ?i spa?iile dintre widget-uri
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    if (mapData.isEmpty()) return;

    // Calcul�m dimensiunile celulelor pentru a umple complet fereastra
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

            // Stil special pentru col?urile bazei
            if ((row == 1 && col == 1) || (row == 1 && col == mapData[row].size() - 2) ||
                (row == mapData.size() - 2 && col == 1) || (row == mapData.size() - 2 && col == mapData[row].size() - 2)) {
                style = "background-color: white; border-radius: 5px; border: 0px; margin: 0px; padding: 0px;";
            }

            cell->setStyleSheet(style);

            // Conect�m click-ul celulei
            connect(cell, &ClickableLabel::clicked, this, &MainWindow::onCellClicked);

            gridLayout->addWidget(cell, row, col);
        }
    }

    // For?�m actualizarea layout-ului
    gridLayout->update();
    this->update();
}

// Ad�ug�m metoda resizeEvent pentru a recalcula dimensiunile la redimensionare
/*void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event); // Apel�m metoda p�rintelui
    initializeMap(); // Recalculeaz� dimensiunile ?i redeseneaz� celulele
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
