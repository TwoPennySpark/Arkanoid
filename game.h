#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "paddle.h"
#include "ball.h"

class Game: public QGraphicsView
{
public:
    Game(QWidget* parent=0);            //Конструктор класса
    QGraphicsScene* scene;              //Создание сцены
    Paddle* paddle;                     //Создание лопатки
    Ball* ball;                         //Создание шарика
    bool gameIsOver;                    //Переменная, отвечающая за окончание игры
    bool gameWon;                       //Переменная, отвечающая за выигрыш или поражение
    QGraphicsTextItem* GameOverText;    //Текст, появляющийся на экране в случае поражения
    QGraphicsTextItem* VictoryText;     //Текст, появляющийся на экране в случае победы
    void start();                       //Функция, описывающая правила игры
    void createBlockRow(double y);      //Функция, создающая ряды из блоков
    void gameOver();                    //Функция, выводящая на экран текст, в случае завершения игры
 private:
    void keyPressEvent(QKeyEvent*);     //Функция, принимающая значения с клавиатуры, отвечает за перемещение лопатки и запуск шарика, а также за возобновление или конец игры в случае победы или поражения
};

#endif //GAME_H
