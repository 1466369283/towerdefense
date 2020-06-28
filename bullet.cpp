#include "bullet.h"
#include "enemy.h"
#include "easymode.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize Bullet::ms_fixedSize(8, 8);

Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
               EasyMode *game, int kind, int fire, qreal slow, const QPixmap &sprite/* = QPixmap("://images/bullet1.png")*/)
    : m_startPos(startPos)
    , m_targetPos(targetPoint)
    , m_sprite(sprite)
    , m_currentPos(startPos)
    , m_target(target)
    , m_game(game)
    , m_damage(damage)
    , bulletKind(kind)
    , fire_attack(fire)
    , slow_speed(slow)
{}

void Bullet::move()
{
    static const int duration = 100;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));
    animation->start();
}

void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(m_currentPos, m_sprite);
}

QPoint Bullet::currentPos() const
{
    return m_currentPos;
}

void Bullet::setCurrentPos(QPoint pos)
{
    m_currentPos = pos;
}

void Bullet::hitTarget()
{
    if (m_game->enemyList().indexOf(m_target) != -1)
        m_target->getDamage(this);
    m_game->removedBullet(this);
}

NormalBullet::NormalBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,EasyMode *game, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game)
{

}

FireBullet::FireBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, EasyMode *game, int kind, int fireattack, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, fireattack, 1, sprite)
{

}

IceBullet::IceBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, EasyMode *game, int kind, qreal slow, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, 0, slow, sprite)
{

}

