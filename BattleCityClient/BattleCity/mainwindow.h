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
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void initializeMap();
    void loadMapFromFile(const QString& filePath);

private slots:
    void onCellClicked(int row, int col);

private:
    Ui::MainWindow* ui;
    QGridLayout* gridLayout;
    QVector<QVector<int>> mapData;
};

#endif // MAINWINDOW_H
