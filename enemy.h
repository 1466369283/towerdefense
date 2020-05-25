#ifndef ENEMY_H
#define ENEMY_H
//#pragma once//仅编译一次，解决类的包含引用的编译错误问题


#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>


class WayPoint;
class QPainter;
class MainWindow;
class Tower;
class EasyMode;

class Enemy:public QObject
{
Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, EasyMode *game, const  QPixmap &sprite= QPixmap("://images/enemy.png"));
    static const QSize ms_fixedSize;
    bool m_active;
    void draw(QPainter *painter);
    void move();

public slots:
    void doActivate();
private:
    int m_maxHp;
    int m_currentHp;
    double m_walkingSpeed;
    QPoint m_pos;
    QPixmap m_sprite;
    WayPoint *m_destinationWayPoint;
    double m_rotationSprite;
    EasyMode *m_game;

};

#endif // ENEMY_H
