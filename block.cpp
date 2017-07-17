#include "block.h"
#include <QBrush>

Block::Block(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    setRect(0,0,80,30);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(238,195,55,255));
    setBrush(brush);
}
