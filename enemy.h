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

    void draw(QPainter *painter) const;
    void move();
    void getDamage(Bullet *bullet);
    void getRemoved();
    void getAttacked(Tower *attacker);
    void getFireDamage(int damage);
    void gotLostSight(Tower *attacker);
    void canRemove();
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
    qreal           m_normalSpeed; //正常速度
    qreal           fireattack; //每0.5秒钟受到多少火焰伤害
    qreal           m_slowSpeed; //寒冰状态的速度
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
