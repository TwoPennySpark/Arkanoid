#ifndef BALL_H
#define BALL_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>
#include <QWidget>

class Ball: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Ball(QGraphicsItem* parent = 0);    //Конструктор класса
    double xV;                          //Переменная, отвечающая за скорость шарика по оси абцисс
    double yV;                          //Переменная, отвечающая за скорость шарика по оси ординат
   // bool preGame;
    QTimer* moveTimer;
    QTimer* followTimer;
public slots:
    void move();                        //Слот, описывающий движение мяча после запуска
    void followPaddle();                //Слот, отвечающий за перемещение мячика вместе с лопаткой, до запуска
private:
    void reachBorder();                 //Метод, отвечающий за столкновения шарика с границей экрана, меняет его xV на -xV
    void handlePaddleCollision();       //Метод, отвечающий за столкновение шарика с лопаткой, меняет его yV на -yV
    void handleBlockCollision();        //Метод, отвечающий за столкновение шарика с одним из блоков
    void loseBall();                    //Метод, вызвающийся тогда, когда шарик выходит за границы экрана (игра проиграна)
};

#endif // BALL_H
