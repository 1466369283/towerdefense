#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class WayPoint;
class QPainter;
class EasyMode;
class Tower;
class Bullet;

class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, EasyMode *game, const QPixmap &sprite = QPixmap("://images/enemy1.png"));
    ~Enemy();
    void move();
    void canRemove();
    void getRemoved();
    void getAttacked(Tower *attacker);
    void getDamage(Bullet *bullet);
    void gotLostSight(Tower *attacker);
    void getFireDamage(int damage);
    void draw(QPainter *painter) const;
    QPoint pos() const;
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    int             fire;
    int             fireLevel;
    int             ice;
    int             iceLevel;
    int             HPdamage;
    int             enemyKind;
    int             award;
    qreal			m_walkingSpeed;
    qreal			m_rotationSprite;
    qreal           fireattackLevel;
    qreal           antiSlowspeed;
    qreal           m_normalSpeed;
    qreal           fireattack;
    qreal           m_slowSpeed;
    QPoint			m_pos;
    WayPoint *		m_destinationWayPoint;
    EasyMode *	    m_game;
    QList<Tower *>	m_attackedTowersList;
    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;
public slots:
    void doActivate();
};

class normalEnemy:public Enemy{
    Q_OBJECT
public:
    normalEnemy(WayPoint *startWayPoint, EasyMode *game, const QPixmap &sprite = QPixmap("://images/enemy1.png"));
};

class iceEnemy:public Enemy{
    Q_OBJECT
public:
    iceEnemy(WayPoint *startWayPoint, EasyMode *game, const QPixmap &sprite = QPixmap("://images/enemy2.png"));
};

class fireEnemy:public Enemy{
    Q_OBJECT
public:
    fireEnemy(WayPoint *startWayPoint, EasyMode *game, const QPixmap &sprite = QPixmap("://images/enemy3.png"));
};

class bossEnemy:public Enemy{
    Q_OBJECT
public:
    bossEnemy(WayPoint *startWayPoint,EasyMode *game, const QPixmap &sprite = QPixmap("://images/boss.png"));
};

#endif // ENEMY_H
