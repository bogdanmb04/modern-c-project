#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include "ClickableLabel.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

// Constructorul clasei MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gridLayout(new QGridLayout())
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    gridLayout->setSpacing(0);
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);


    // Încarcă harta din fișierul map.txt
    loadMapFromFile("map.txt");


    // Inițializează UI-ul
    initializeMap();


}

// Destructorul
MainWindow::~MainWindow()
{
    delete ui;
}

// Funcția care citește harta din fișier
void MainWindow::loadMapFromFile(const QString &filePath)
{
    QFile file(filePath);  // Deschide fișierul pentru citire

    // Verifică dacă fișierul se deschide corect
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Eroare", "Nu s-a putut deschide fișierul: " + file.errorString());
        return;  // Ieși din funcție dacă fișierul nu este accesibil
    }

    QTextStream in(&file);  // Creează un stream pentru citire
    mapData.clear();        // Curăță matricea mapData existentă

    int row = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();  // Citește o linie din fișier

        QVector<int> rowData;
        for (int col = 0; col < line.length(); ++col) {
            // Adaugă valoarea corespunzătoare în matrice pe baza caracterului
            if (line[col] == '0')
                rowData.append(0);
            else if (line[col] == '1')
                rowData.append(1);
            else if (line[col] == '2')
                rowData.append(2);
        }
        mapData.append(rowData);  // Adaugă linia citită în matricea principală
        row++;
    }

    file.close();  // Închide fișierul

    // Verifică dacă fișierul conține date
    if (mapData.isEmpty()) {
        QMessageBox::warning(this, "Eroare", "Fișierul este gol sau nu conține date valide.");
        return;
    }
}


// Funcția care construiește UI-ul pe baza hărții
void MainWindow::initializeMap()
{
    for (int row = 0; row < mapData.size(); ++row) {
        for (int col = 0; col < mapData[row].size(); ++col) {
            ClickableLabel *cell = new ClickableLabel(this);
            cell->setFixedSize(60, 60);
            cell->setCoordinates(row, col); // Setează coordonatele pentru etichetă

            // Setează stilul pe baza valorii din mapData
            if (mapData[row][col] == 1) {
                cell->setStyleSheet("background-color: brown; border: 1px solid black;margin: 0;");
            } else if (mapData[row][col] == 2) {
                cell->setStyleSheet("background-color: red; border: 1px solid black;margin: 0;");
            } else {
                cell->setStyleSheet("background-color: black; border: 1px solid black;margin: 0;");
            }

            // Setează colțurile la culoare albă cu colțuri rotunjite
            if ((row == 0 && col == 0) || (row == 0 && col == mapData[row].size() - 1) ||
                (row == mapData.size() - 1 && col == 0) || (row == mapData.size() - 1 && col == mapData[row].size() - 1)) {
                cell->setStyleSheet("background-color: white; border-radius: 5px; width: 10px; height: 5px;");
            }

            // Conectează semnalul de click la slotul corespunzător
            connect(cell, &ClickableLabel::clicked, this, &MainWindow::onCellClicked);

            gridLayout->addWidget(cell, row, col);
        }
    }
}

// Slotul care gestionează clicurile pe celule
void MainWindow::onCellClicked(int row, int col)
{
    // Verifică dacă zidul este destructibil
    if (mapData[row][col] == 1) {
        // Actualizează matricea cu valoarea "gol"
        mapData[row][col] = 0;

        // Obține widget-ul la poziția respectivă
        QWidget *widget = gridLayout->itemAtPosition(row, col)->widget();
        QLabel *cell = qobject_cast<QLabel *>(widget);

        if (cell) {
            // Actualizează stilul grafic al celulei
            cell->setStyleSheet("background-color: black; border: 1px solid black;");
        }
    } else if (mapData[row][col] == 2) {
        // Mesaj pentru zid indestructibil
     //   QMessageBox::information(this, "Info", "Acest perete este nedestructibil!");
    }
}



