#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class EasyMode;
class QTimer;

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, EasyMode *game, const QPixmap &sprite = QPixmap("://images/tower1.png"),int attackRange = 120, int damage = 10, int fireRate = 300, int level = 1);
    ~Tower();

    virtual void draw(QPainter *painter) const;
    void checkEnemyInRange();
    void targetKilled();
    void attackEnemy();
    void chooseEnemyForAttack(Enemy *enemy);
    void damageEnemy();
    void lostSightOfEnemy();

    virtual void levelup() = 0;
    int             m_level;
     QTimer *		m_fireRateTimer;


    const QPoint	m_pos; //塔的圆心

private slots:
    virtual void shootWeapon() =0;

protected:
    bool			m_attacking;
    qreal			m_rotationSprite;

    Enemy *			m_chooseEnemy;
    EasyMode *      m_game;


    int				m_attackRange;	// 代表塔可以攻击到敌人的距离
    int				m_damage;		// 代表攻击敌人时造成的伤害
    int				m_fireRate;		// 代表再次攻击敌人的时间间隔
    const QPixmap	m_sprite;

    static const QSize ms_fixedSize;
};

class NormalTower: public Tower
{
    Q_OBJECT
public:
    NormalTower(QPoint pos, EasyMode *game, const QPixmap &sprite = QPixmap("://images/tower1.png"));
    ~NormalTower();

    void levelup();

protected slots:
    virtual void shootWeapon();
};

class FireTower : public Tower
{
    Q_OBJECT
public:
    FireTower(QPoint pos, EasyMode *game, const QPixmap &sprite = QPixmap("://images/tower2.png"));
    ~FireTower();

    void levelup();

protected slots:
    virtual void shootWeapon();

private:
    int fireattack; //每秒的灼烧伤害
};

class IceTower : public Tower
{
    Q_OBJECT
public:
    IceTower(QPoint pos, EasyMode *game, const QPixmap &sprite = QPixmap("://images/tower3.png"));
    ~IceTower();

    void levelup();

protected slots:
    virtual void shootWeapon();

private:
    int slowspeed; //减慢速度百分比
};

#endif // TOWER_H
