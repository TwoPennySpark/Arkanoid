#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>

class Paddle: public QGraphicsRectItem
{
public:
    Paddle(QGraphicsItem* parent=0);    //Конструктор класса
    int paddle_x;                       //Координата лопатки по оси абцисс
};

#endif // PADDLE_H
