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
    void chooseEnemyForAttack(Enemy *enemy);
    void attackEnemy();
    void damageEnemy();
    void lostSightOfEnemy();
    void targetKilled();
    virtual void levelup() = 0;
    int             m_level;
    QTimer *		m_fireRateTimer;
    const QPoint	m_pos;
private slots:
    virtual void shootWeapon() =0;
protected:
    bool			m_attacking;
    qreal			m_rotationSprite;
    Enemy *			m_chooseEnemy;
    EasyMode *      m_game;
    int				m_attackRange;
    int				m_damage;
    int				m_fireRate;
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
    int fireattack;
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
    int slowspeed;
};

#endif // TOWER_H
