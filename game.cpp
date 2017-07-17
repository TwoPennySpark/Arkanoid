#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "block.h"
#include <stdio.h>
#include <QBrush>
#include <QGraphicsObject>
#include <QString>
#include <QKeyEvent>
#include <QList>
#include <QApplication>
#include <QFont>
#include <QImage>

extern Game* game;
extern Ball* ball;

Game::Game(QWidget *parent): QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,655,600);
    setScene(scene);

    ball = new Ball();
    paddle = new Paddle();
    gameIsOver = false;
    gameWon = false;

    GameOverText = new QGraphicsTextItem(QString("   Game Over!\n\n Try again Y/N?"));
    VictoryText = new QGraphicsTextItem(QString("   You Won!!!\n\n Try again Y/N?"));
    GameOverText->setDefaultTextColor(QColor(Qt::white));
    VictoryText->setDefaultTextColor(QColor(Qt::white));
    GameOverText->setPos(210,280);
    VictoryText->setPos(210,280);

    setBackgroundBrush(QBrush(QImage(":/img/bg.png")));
}

void Game::createBlockRow(double y)
{
    for (size_t k = 0, j = 8; k < j; ++k)
    {
        for (size_t i = k, n = 8; i < n-k; ++i)
        {
            Block* block = new Block();
            block->setPos(i*82,y);
            scene->addItem(block);
        }
        y += 32;
    }
}

void Game::start()
{
    if (gameIsOver == false)
    {
        scene->addItem(ball);
        paddle->setPos(275,575);
        scene->addItem(paddle);
    }
    if (gameIsOver == true)
    {
        if(gameWon == true)
            scene->removeItem(VictoryText);
        else
            scene->removeItem(GameOverText);

        QList<QGraphicsItem*> allItems = scene->items();
        for (size_t i = 0,q = scene->items().size() ; i < q ; ++i)
        {
            Block* block = dynamic_cast<Block*>(allItems[i]);
            if (block)
            {
                scene->removeItem(block);
            }
        }
        paddle->setPos(275,575);
        ball->moveTimer->stop();
        ball->followTimer->start(15);

        gameIsOver = false;
        gameWon = false;
    }
    createBlockRow(0);
}

void Game::keyPressEvent(QKeyEvent* e)
{
    if (e->key()==Qt::Key_Right && gameIsOver == false)
    {
        paddle->paddle_x += 50;
        paddle->setPos(paddle->paddle_x,575);
    }
    if (e->key()==Qt::Key_Left && gameIsOver == false)
    {
        paddle->paddle_x -= 50;
        paddle->setPos(paddle->paddle_x,575);
    }
    if(e->key()==Qt::Key_Space && gameIsOver == false )
    {
        ball->yV = -4;
        ball->xV = 4;
        ball->followTimer->stop();
        ball->moveTimer->start(10);
    }
    if(e->key()==Qt::Key_Y && gameIsOver == true)
    {
        start();
    }
    if(e->key()==Qt::Key_N && gameIsOver == true)
    {
        QApplication::quit();
    }
}

void Game::gameOver()
{
    gameIsOver = true;
    QFont titleFont("comic sans",25 ,QFont::Light);
    if(scene->items().size() == 2)
    {
        VictoryText->setFont(titleFont);
        scene->addItem(VictoryText);
        gameWon = true;
    }
    else
    {
        GameOverText->setFont(titleFont);
        scene->addItem(GameOverText);
    }
}
