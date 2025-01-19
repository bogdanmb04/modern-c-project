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
enum class Direction {
    Up,
    Down,
    Left,
    Right
};

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
    QVector<QVector<QPair<int, QString>>> mapData;
    QTimer* coinTimer;
    QTimer* objectSpawnTimer;
    HttpManager httpManager;

    QString userId;
    Direction playerDirection;

    void loadMapFromServer();
    void initializeMap();
    void placeCoins();
    void updateMapView(const QJsonArray& layout);
    void spawnRandomObjects();
    bool placeCoinAtRandomLocation();
    void triggerExplosion(int row, int col);
    void placeRandomBombsAround(int row, int col);
    void movePlayer(QString playerID, Direction direction);
    void keyPressEvent(QKeyEvent* event);
   
private slots:
    void BackButtonClicked();
    void onCellClicked(int row, int col);
    
public slots:
    void onLoginSuccess(const QString& userId);

signals:
    void loginSuccess(const QString& userId);
};

#endif // MAINWINDOW_H
