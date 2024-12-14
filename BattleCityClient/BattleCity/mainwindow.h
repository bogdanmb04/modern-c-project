#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QVector>
#include "HttpManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void initializeMap();
    void loadMapFromServer();
    
private slots:
    void onCellClicked(int row, int col);
   // void resizeEvent(QResizeEvent* event) override;

private:
    Ui::MainWindow* ui;
    QGridLayout* gridLayout;
    QVector<QVector<int>> mapData;
    HttpManager httpManager;
};

#endif // MAINWINDOW_H
