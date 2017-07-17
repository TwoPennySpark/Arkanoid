#include "ball.h"
#include <QTimer>
#include <QBrush>
#include "game.h"
#include "paddle.h"
#include "block.h"
#include <stdio.h>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QWidget>

extern Game* game;

Ball::Ball(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent)
{
    //setPixmap(QPixmap(":img.qrc/img/ball4.png"));
    setRect(0, 0, 50, 50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(90,60,90,255));
    setBrush(brush);

    xV = 2;
    yV = -2;

    moveTimer = new QTimer();
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));

    followTimer = new QTimer();
    connect(followTimer,SIGNAL(timeout()),this,SLOT(followPaddle()));

    followTimer->start(15);
}

void Ball::move()
{
    reachBorder();
    handlePaddleCollision();
    handleBlockCollision();
    loseBall();

    moveBy(xV,yV);
}

void Ball::followPaddle()
{
    setPos(game->paddle->pos().x()+27,game->paddle->pos().y()-53);
}

void Ball::reachBorder()
{
    double screenW = game->width();

    double ballx = pos().x();
    double bally = pos().y();

    if (ballx <= -10)
    {
        xV = -1 * xV;
    }

    if (ballx >= screenW-32)
    {
        xV = -1 * xV;
    }

    if (bally <= 0)
    {
        yV = -1 * yV;
    }
}

void Ball::handlePaddleCollision()
{
        if (collidesWithItem(game->paddle))
        {
            yV = -1 * yV;
            return;
        }
}

void Ball::handleBlockCollision()
{
    QList<QGraphicsItem*> cItems = collidingItems();
    double ballx;
    double bally;
    double blockx;
    double blocky;

    for (size_t i = 0, n = cItems.size(); i < n; ++i)
    {
        Block* block = dynamic_cast<Block*>(cItems[i]);
        if (block)
        {
            ballx = pos().x();
            bally = pos().y();
            blockx = block->pos().x();
            blocky = block->pos().y();

            game->scene->removeItem(block);
            delete block;
            if(game->scene->items().size()==2)
            {
                yV = 0;
                xV = 0;
                game->gameOver();
            }

            if (bally > blocky+24 && yV < 0 )
            {
                yV = -1 * yV;
                continue;
            }

            if (blocky > bally+28 && yV > 0 )
            {
                yV = -1 * yV;
                continue;
            }

            if (ballx > blockx+71 && xV < 0 )
            {
                xV = -1 * xV;
                continue;
            }

            if (blockx > ballx+24 && xV > 0 )
            {
                xV = -1 * xV;
                continue;
            }
        }
    }
}

void Ball::loseBall()
{
    if(pos().y()>=600)
    {
        setPos(900,300);
        xV = 0;
        yV = 0;
        game->gameOver();
    }
}
