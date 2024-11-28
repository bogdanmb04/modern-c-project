#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = nullptr) : QLabel(parent) {}

    void setCoordinates(int row, int col) { m_row = row; m_col = col; }

signals:
    void clicked(int row, int col);

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            emit clicked(m_row, m_col);
        }
    }

private:
    int m_row, m_col;
};

#endif // CLICKABLELABEL_H
