#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGridLayout *gridLayout;
    QVector<QVector<int>> mapData;  // Keep the original name or rename if desired
    void  initializeMap();

private slots:
    void onCellClicked(int row, int col);  // Slot for cell click (no need to pass QLabel*)

};

#endif // MAINWINDOW_H

