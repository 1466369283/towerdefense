#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class EasyMode;

class Bullet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)
public:
    Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, EasyMode *game, int kind = 0, int fire = 0, qreal slow = 1, const QPixmap &sprite = QPixmap("://images/bullet1.png"));
    void setCurrentPos(QPoint pos);
    void move();
    void draw(QPainter *painter) const;
    QPoint currentPos() const;
    friend class Enemy;
private slots:
    void hitTarget();
protected:
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
    const QPixmap	m_sprite;
    QPoint			m_currentPos;
    Enemy *			m_target;
    EasyMode *	    m_game;
    int				m_damage;
    int             bulletKind;
    int             fire_attack;
    qreal           slow_speed;
    static const QSize ms_fixedSize;
};

class NormalBullet: public Bullet
{
    Q_OBJECT
public:
    NormalBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, EasyMode *game, const QPixmap &sprite = QPixmap("://images/bullet1.png"));
};

class FireBullet: public Bullet
{
    Q_OBJECT
public:
    FireBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, EasyMode *game, int kind = 1, int fire = 1, const QPixmap &sprite = QPixmap("://images/bullet2.png"));

};

class IceBullet: public Bullet
{
    Q_OBJECT
public:
    IceBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, EasyMode *game, int kind = 2, qreal slow = 0.5, const QPixmap &sprite = QPixmap("://images/bullet3.png"));

};

#endif // BULLET_H
