#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVector>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRandomGenerator>
#include "ClickableLabel.h"
#include "httpmanager.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

signals:
    void backToBattleCity();

private:
    Ui::MainWindow* ui;
    QGridLayout* gridLayout;
    QVector<QVector<int>> mapData;
    QTimer* coinTimer;
    QTimer* objectSpawnTimer;
    HttpManager httpManager;

    void loadMapFromServer();
    void initializeMap();
    void placeCoins();
    void spawnRandomObjects();
    bool placeCoinAtRandomLocation();
    void triggerExplosion(int row, int col);
    void placeRandomBombsAround(int row, int col);

private slots:
    void BackButtonClicked();
    void onCellClicked(int row, int col);
};

#endif // MAINWINDOW_H
