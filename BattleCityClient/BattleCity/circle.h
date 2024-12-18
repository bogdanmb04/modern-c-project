#ifndef CIRCLE_H
#define CIRCLE_H

#include <QWidget>

class Circle : public QWidget
{
    Q_OBJECT

public:
    explicit Circle(QWidget* parent = nullptr); 
    void setFilled(bool filled);             
    bool isFilled() const;                     

protected:
    void paintEvent(QPaintEvent* event) override; 

private:
    bool m_filled; 
};

#endif // CIRCLE_H
