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


Tower::~Tower()
{
    delete m_fireRateTimer;
    m_fireRateTimer = nullptr;
}

void Tower::checkEnemyInRange()
{
    if (m_chooseEnemy)
    {
        // 这种情况下,需要旋转炮台对准敌人
        // 向量标准化
      //  QVector2D normalized(m_chooseEnemy->pos() - m_pos);
       // normalized.normalize();
      //  m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x()))+90;

        // 如果敌人脱离攻击范围
        if (!collisionWithCircle(m_pos, m_attackRange, m_chooseEnemy->pos(), 1))
            lostSightOfEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
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

void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::white);
    // 绘制攻击范围
    //painter->drawEllipse(m_pos, m_attackRange, m_attackRange);  //画攻击范围

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    // 绘制炮塔并选择炮塔
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint.x()+20,offsetPoint.y()-50 ,70,140,m_sprite);
    //painter->drawPixmap(offsetPoint.x(),offsetPoint.y() -30,107,95+30,m_sprite);
    painter->restore();
}

void Tower::attackEnemy()
{
    m_fireRateTimer->start(m_fireRate);
}

void Tower::chooseEnemyForAttack(Enemy *enemy)
{
    Q_ASSERT(enemy);
    m_chooseEnemy = enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);
}

void Tower::targetKilled()
{
    if (m_chooseEnemy)
        m_chooseEnemy = nullptr;

    //停止计时器
    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}

void Tower::lostSightOfEnemy()
{
    m_chooseEnemy->gotLostSight(this);
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
    if (m_level == 5) //5级为最高级
        return;
    m_level++;
    m_damage += 5; //每升一级子弹加5点伤害
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
    if (m_level == 5) //5级为最高级
        return;
    m_level++;
    m_damage += 5; //每升一级，火焰子弹加5点伤害
    fireattack += 1; //每升一级，火焰子弹加1点灼烧伤害
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
    if (m_level == 5) //5级为最高级
        return;
    m_level++;
    m_damage += 5; //每升一级，寒冰子弹加5点伤害
    slowspeed -= 0.1; //每升一级，寒冰子弹增加10%减速效果
}

void IceTower::shootWeapon()
{
    Bullet *bullet = new IceBullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game, 2, 0.5);
    bullet->move();
    m_game->addBullet(bullet);
}


