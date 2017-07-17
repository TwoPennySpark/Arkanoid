#include "paddle.h"
#include <QBrush>

Paddle::Paddle(QGraphicsItem* parent)
{
    setRect(0,0,100,15);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(Qt::darkGray));
    setBrush(brush);
    paddle_x = 275;
}
