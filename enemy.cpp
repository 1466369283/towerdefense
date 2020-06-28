#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "utility.h"
#include "easymode.h"
#include "audioplayer.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>
#include "bullet.h"

static const int Health_Bar_Width = 20;

const QSize Enemy::ms_fixedSize(107,95);

Enemy::Enemy(WayPoint *startWayPoint, EasyMode *game, const QPixmap &sprite/* = QPixmap("://images/enemy1.png")*/)
    : QObject(nullptr)
    , m_active(false)
    , m_maxHp(40)
    , m_currentHp(40)
    , fire(0)
    , ice(0)
    , enemyKind(1)
    , award(200)
    , m_walkingSpeed(1.0)
    , m_rotationSprite(0.0)
    , fireattackLevel(1.0)
    , antiSlowspeed(1.0)
    , m_normalSpeed(2.0)
    , m_slowSpeed(1.0)
    , m_pos(startWayPoint->pos())
    , m_destinationWayPoint(startWayPoint->nextWayPoint())
    , m_game(game)
    , m_sprite(sprite)
{
    m_attackedTowersList.clear();
}

void Enemy::draw(QPainter *painter) const
{
    if (!m_active)
        return;
    painter->save();
    QPoint healthBarPoint = m_pos + QPoint(-ms_fixedSize.width()/3+6, -ms_fixedSize.height() /2-10);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 5));
    painter->drawRect(healthBarBackRect);
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 5));
    painter->drawRect(healthBarRect);
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

void Enemy::move()
{
    if (!m_active)
        return;

    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        if (m_destinationWayPoint->nextWayPoint())
        {
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            m_game->getHpDamage(HPdamage);
            m_game->removedEnemy(this);
            return;
        }
    }
    QPoint targetPoint = m_destinationWayPoint->pos();
    qreal movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;
}

Enemy::~Enemy()
{
    m_attackedTowersList.clear();
    m_destinationWayPoint = nullptr;
    m_game = nullptr;
}

void Enemy::getRemoved()
{
    if (!m_attackedTowersList.empty())
    foreach (Tower *attacker, m_attackedTowersList)
        attacker->targetKilled();
    m_game->removedEnemy(this);
}

void Enemy::doActivate()
{
    m_active = true;
}

void Enemy::canRemove()
{
    if (m_currentHp <= 0){
        switch(enemyKind){
        case(1):
            m_game->audioPlayer()->playSound(normalEnemyDestorySound);
            break;
        case(2):
            m_game->audioPlayer()->playSound(iceEnemyDestorySound);
            break;
        case(3):
            m_game->audioPlayer()->playSound(fireEnemyDestorySound);
            break;
        case(4):
            m_game->audioPlayer()->playSound(bossEnemyDestorySound);
            break;
        }
        m_game->awardGold(award);
        getRemoved();
    }
}

void Enemy::getDamage(Bullet *bullet){
    m_currentHp -= bullet->m_damage;

    switch(bullet->bulletKind)
    {
        case 0://NormalBullet
            m_game->audioPlayer()->playSound(NormalBulletSound);
            break;
        case 1://FireBullet
            m_game->audioPlayer()->playSound(FireBulletSound);
            fire = fireLevel;
            fireattack = bullet->fire_attack*fireattackLevel;
            break;
        case 2://IceBullet
            m_game->audioPlayer()->playSound(IceBulletSound);
            ice = iceLevel;
            m_slowSpeed = qMin(m_normalSpeed * bullet->slow_speed*antiSlowspeed, m_slowSpeed);
            m_walkingSpeed = m_slowSpeed;
            break;

    }
    canRemove();
}

QPoint Enemy::pos() const
{
    return m_pos;
}

void Enemy::gotLostSight(Tower *attacker)
{
    Q_ASSERT(attacker);
    m_attackedTowersList.removeOne(attacker);
}


void Enemy::getAttacked(Tower *attacker)
{
    Q_ASSERT(attacker);
    m_attackedTowersList.push_back(attacker);
}

void Enemy::getFireDamage(int damage)
{
    m_currentHp -= damage;
    canRemove();
}

normalEnemy::normalEnemy(WayPoint *startWayPoint, EasyMode *game, const QPixmap &sprite/* = QPixmap("://images/enemy1.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap("://images/enemy1.png")*/)
{
    this->fireLevel=15;
    this->iceLevel=15;
    this->HPdamage=1;
    this->m_rotationSprite = 0.0;
    this->m_pos=startWayPoint->pos();
    this->m_destinationWayPoint=startWayPoint->nextWayPoint();
}

bossEnemy::bossEnemy(WayPoint *startWayPoint, EasyMode *game, const QPixmap &sprite/* = QPixmap("://images/boss.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap("://images/boss.png")*/)
{
    this->enemyKind=4;
    this->award=300;
    this->m_maxHp = 300;
    this->m_currentHp = 300;
    this->m_normalSpeed=3.0;
    this->m_walkingSpeed=3.0;
    this->antiSlowspeed=1.5;
    this->fireattack=1.0;
    this->fireLevel=10;
    this->iceLevel=10;
    this->HPdamage=5;
    this->m_rotationSprite = 0.0;
    this->m_pos=startWayPoint->pos();
    this->m_destinationWayPoint=startWayPoint->nextWayPoint();
}

fireEnemy::fireEnemy(WayPoint *startWayPoint, EasyMode *game, const QPixmap &sprite/* = QPixmap("://images/enemy3.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap("://images/enemy3.png")*/)
{
    this->enemyKind=3;
    this->award=200;
    this->m_walkingSpeed=2.0;
    this->m_maxHp = 150;
    this->m_currentHp = 150;
    this->antiSlowspeed=1.5;
    this->fireLevel=10;
    this->iceLevel=20;
    this->HPdamage=3;
    this->m_rotationSprite = 0.0;
    this->m_pos=startWayPoint->pos();
    this->m_destinationWayPoint=startWayPoint->nextWayPoint();
}

iceEnemy::iceEnemy(WayPoint *startWayPoint, EasyMode *game, const QPixmap &sprite/* = QPixmap("://images/enemy2.png")*/)
    :Enemy(startWayPoint, game,sprite/* = QPixmap("://images/enemy2.png")*/)
{
    this->enemyKind=2;
    this->award=150;
    this->m_maxHp = 150;
    this->m_walkingSpeed=0.5;
    this->m_currentHp = 150;
    this->antiSlowspeed=2.0;
    this->fireLevel=20;
    this->iceLevel=10;
    this->HPdamage=2;
    this->m_rotationSprite = 0.0;
    this->m_pos=startWayPoint->pos();
    this->m_destinationWayPoint=startWayPoint->nextWayPoint();
}
