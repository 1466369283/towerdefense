#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "easymode.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Tower::ms_fixedSize(107,95);

Tower::Tower(QPoint pos, EasyMode *game, const QPixmap &sprite, int attackRange, int damage, int fireRate, int level)
    : m_level(level)
    , m_attacking(false)
    , m_rotationSprite(0.0)
    , m_chooseEnemy(nullptr)
    , m_game(game)
    , m_attackRange(attackRange)
    , m_damage(damage)
    , m_fireRate(fireRate)//开火频率
    , m_pos(pos)
    , m_sprite(sprite)
{
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::white);
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint.x()+20,offsetPoint.y()-50 ,70,140,m_sprite);
    painter->restore();
}

void Tower::checkEnemyInRange()
{
    if (m_chooseEnemy)
    {
        if (!collisionWithCircle(m_pos, m_attackRange, m_chooseEnemy->pos(), 1))
            lostSightOfEnemy();
    }
    else
    {
        QList<Enemy *> enemyList = m_game->enemyList();
        foreach (Enemy *enemy, enemyList)
        {
            if (collisionWithCircle(m_pos, m_attackRange, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}

void Tower::chooseEnemyForAttack(Enemy *enemy)
{
    Q_ASSERT(enemy);
    m_chooseEnemy = enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);
}

void Tower::attackEnemy()
{
    m_fireRateTimer->start(m_fireRate);
}

void Tower::lostSightOfEnemy()
{
    m_chooseEnemy->gotLostSight(this);
    if (m_chooseEnemy)
        m_chooseEnemy = nullptr;
    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}

void Tower::targetKilled()
{
    if (m_chooseEnemy)
        m_chooseEnemy = nullptr;
    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}

NormalTower::NormalTower(QPoint pos, EasyMode *game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{

}

NormalTower::~NormalTower()
{

}

void NormalTower::shootWeapon()
{
    Bullet *bullet = new NormalBullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet->move();
    m_game->addBullet(bullet);
}

void NormalTower::levelup()
{
    if (m_level == 5)
        return;
    m_level++;
    m_damage += 5;
}

IceTower::IceTower(QPoint pos, EasyMode *game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{

}

IceTower::~IceTower()
{

}

void IceTower::levelup()
{
    if (m_level == 5)
        return;
    m_level++;
    m_damage += 5;
    slowspeed -= 0.1;
}

void IceTower::shootWeapon()
{
    Bullet *bullet = new IceBullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game, 2, 0.5);
    bullet->move();
    m_game->addBullet(bullet);
}

FireTower::FireTower(QPoint pos, EasyMode *game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{

}

FireTower::~FireTower()
{

}

void FireTower::shootWeapon()
{
    Bullet *bullet = new FireBullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game, 1, 1);
    bullet->move();
    m_game->addBullet(bullet);
}

void FireTower::levelup()
{
    if (m_level == 5)
        return;
    m_level++;
    m_damage += 5;
    fireattack += 1;
}

Tower::~Tower()
{
    delete m_fireRateTimer;
    m_fireRateTimer = nullptr;
}

