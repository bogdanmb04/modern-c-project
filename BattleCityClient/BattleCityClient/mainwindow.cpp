

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include "ClickableLabel.h"
#include <QMessageBox>

// 0 = empty(black), 1 = breakable wall(brown), 2 = unbreakable wall(red)
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
, ui(new Ui::MainWindow)
, gridLayout(new QGridLayout())
, mapData{
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
      {0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 2, 1, 0},
      {2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1, 2},
      {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 2, 2, 2, 1, 0, 0, 1, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
      {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0},
      {0, 0, 1, 1, 2, 2, 0, 0, 0, 0, 2, 1, 1},
      {0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 2, 0, 0},
      {0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}
  }
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    gridLayout->setSpacing(1);
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);

    resize(600, 600);

    initializeMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: initializeMap()
{
    for (int row = 0; row < mapData.size(); ++row) {
        for (int col = 0; col < mapData[row].size(); ++col) {
            ClickableLabel *cell = new ClickableLabel(this);
            cell->setFixedSize(40, 40);
            cell->setCoordinates(row, col); // Set the coordinates for the label

            // Set the initial style based on mapData
            if (mapData[row][col] == 1) {
                cell->setStyleSheet("background-color: brown; border: 1px solid black;");
            } else if (mapData[row][col] == 2) {
                cell->setStyleSheet("background-color: red; border: 1px solid black;");
            } else {
                cell->setStyleSheet("background-color: black; border: 1px solid black;");
            }

            // Set corner cells to white with rounded borders
            if ((row == 0 && col == 0) || (row == 0 && col == mapData[row].size() - 1) ||
                (row == mapData.size() - 1 && col == 0) || (row == mapData.size() - 1 && col == mapData[row].size() - 1)) {
                cell->setStyleSheet("background-color: white; border-radius: 20px; width: 10px; height: 20px;");
            }

            // Connect the clicked signal to the slot
            connect(cell, &ClickableLabel::clicked, this, &MainWindow::onCellClicked);

            gridLayout->addWidget(cell, row, col);
        }
    }
}

void MainWindow::onCellClicked(int row, int col)
{
    // Check the type of wall and respond accordingly
    if (mapData[row][col] == 1) { // Breakable wall
        mapData[row][col] = 0; // Change to empty
        QLabel *cell = qobject_cast<QLabel*>(gridLayout->itemAtPosition(row, col)->widget());
        if (cell) {
            cell->setStyleSheet("background-color: black; border: 1px solid black;"); // Update the appearance
            //  QMessageBox::information(this, "Info", "This wall was breached!");

        }
    } else if (mapData[row][col] == 2) { // Unbreakable wall
        //QMessageBox::information(this, "Info", "This wall is unbreakable!");
    }
}
