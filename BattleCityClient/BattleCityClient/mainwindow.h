#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initializeMap();  // Metodă pentru inițializarea hărții
    void loadMapFromFile(const QString &filePath);  // Metodă pentru încărcarea hărții din fișier

private slots:
    void onCellClicked(int row, int col);  // Slot pentru gestionarea clicurilor pe celule

private:
    Ui::MainWindow *ui;                // UI-ul generat automat de Qt Designer
    QGridLayout *gridLayout;            // Layout-ul pentru celulele hărții
    QVector<QVector<int>> mapData;      // Reprezentarea hărții (0 = liber, 1 = perete destructibil, 2 = perete nedestructibil)
};

#endif // MAINWINDOW_H
