#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = nullptr) : QLabel(parent) {}

signals:
    void clicked(int row, int col);

public:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            emit clicked(row, col);
        }
        QLabel::mousePressEvent(event);
    }

    void setCoordinates(int r, int c) {
        row = r;
        col = c;
    }

private:
    int row;
    int col;
};

#endif // CLICKABLELABEL_H
