#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVector>
#include <QLabel>
#include "httpmanager.h"

class ClickableLabel;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
private slots:
    void onCellClicked(int row, int col);
signals:
    void backToBattleCity();

private:
    void loadMapFromServer();
    void initializeMap();
    void BackButtonClicked();
    void keyPressEvent(QKeyEvent* event) override;
    void sendMoveRequest(int playerID, const QString& direction);
  
    Ui::MainWindow* ui;
    QGridLayout* gridLayout;
    QVector<QVector<int>> mapData;
    HttpManager httpManager;

};

#endif // MAINWINDOW_H
