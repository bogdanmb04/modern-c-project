#include "circle.h"
#include <QPainter> 

Circle::Circle(QWidget* parent)
    : QWidget(parent), m_filled(false)
{
    setFixedSize(30, 30);
}

void Circle::setFilled(bool filled)
{
    if (m_filled != filled) {
        m_filled = filled;
        update();
    }
}

bool Circle::isFilled() const
{
    return m_filled;
}

void Circle::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (m_filled) {
        painter.setBrush(Qt::white);
    }
    else {
        painter.setBrush(Qt::black); 
    }

    painter.setPen(Qt::black); 
    painter.drawEllipse(0, 0, width() - 1, height() - 1); 
}
