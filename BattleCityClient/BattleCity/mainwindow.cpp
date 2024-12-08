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
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);

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
        QMessageBox::warning(this, "Eroare", "Nu s-a putut deschide fisierul: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    mapData.clear();

    int row = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();

        QVector<int> rowData;
        for (int col = 0; col < line.length(); ++col) {

            if (line[col] == '0')
                rowData.append(0);
            else if (line[col] == '1')
                rowData.append(1);
            else if (line[col] == '2')
                rowData.append(2);
            else if (line[col] == '3')
                rowData.append(3);
        }
        mapData.append(rowData);
        row++;
    }

    file.close();


    if (mapData.isEmpty()) {
        QMessageBox::warning(this, "Eroare", "Fisierul este gol sau nu contine date valide.");
        return;
    }
}


void MainWindow::initializeMap()
{
    while (QLayoutItem* item = gridLayout->takeAt(0))
    {
        delete item->widget();
        delete item;
    }

    int cellWidth = this->width() / mapData[0].size();
    int cellHeight = this->height() / mapData.size();
    int cellSize = qMin(cellWidth, cellHeight);

    for (int row = 0; row < mapData.size(); ++row) {
        for (int col = 0; col < mapData[row].size(); ++col) {
            ClickableLabel* cell = new ClickableLabel(this);
            int cellSize = this->width() / mapData[0].size();
            cell->setFixedSize(cellSize, cellSize);
            cell->setCoordinates(row, col);


            if (mapData[row][col] == 1) {
                cell->setStyleSheet("background-color: brown; border: 2 solid black;margin: 0;padding: 0;");
            }
            else if (mapData[row][col] == 2) {
                cell->setStyleSheet("background-color: red; border: 2px solid black;margin: 0;padding: 0;");
            }
            else if (mapData[row][col] == 0) {
                cell->setStyleSheet("background-color: black; border: 2px solid black;margin: 0;padding: 0;");
            }
            else {
                cell->setStyleSheet("background-color: green; border: 2px solid black;margin: 0;padding: 0;");
            }


            if ((row == 1 && col == 1) || (row == 1 && col == mapData[row].size() - 2) ||
                (row == mapData.size() - 2 && col == 1) || (row == mapData.size() - 2 && col == mapData[row].size() - 2)) {
                cell->setStyleSheet("background-color: white; border-radius: 5px; width: 10px; height: 5px;");
            }

            connect(cell, &ClickableLabel::clicked, this, &MainWindow::onCellClicked);

            gridLayout->addWidget(cell, row, col);
        }
    }


}

void MainWindow::onCellClicked(int row, int col)
{
    if (mapData[row][col] == 1) {
        mapData[row][col] = 0;

        QWidget* widget = gridLayout->itemAtPosition(row, col)->widget();
        QLabel* cell = qobject_cast<QLabel*>(widget);

        if (cell) {
            cell->setStyleSheet("background-color: black; border: 1px solid black;");
        }
    }
    else if (mapData[row][col] == 2) {

        //   QMessageBox::information(this, "Info", "Acest perete este nedestructibil!");
    }
}




