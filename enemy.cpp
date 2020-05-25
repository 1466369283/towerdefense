#include "enemy.h"
#include <utility.h>
#include<waypoint.h>
#include<easymode.h>

const QSize Enemy::ms_fixedSize(107, 95);

Enemy::Enemy(WayPoint *startWayPoint, EasyMode *game,const QPixmap &sprite/* = QPixmap(":/images/enemy.png")*/)
    : QObject(0),
      m_pos(startWayPoint->pos()),
      m_sprite(sprite)
{
    m_maxHp = 40;
    m_currentHp = 40;
    m_active = false;
    m_walkingSpeed = 1.0;
    m_rotationSprite = 0.0;
    m_destinationWayPoint = startWayPoint->nextWayPoint();
    m_game = game;

}

void Enemy::draw(QPainter *painter)
{
    if (!m_active)
        return;
    // 血条的长度
    // 其实就是2个方框,红色方框表示总生命,固定大小不变
    // 绿色方框表示当前生命,受m_currentHp / m_maxHp的变化影响
    static const int Health_Bar_Width = 20;
    painter->save();
    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 - 5, -ms_fixedSize.height() / 3);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 2));
    painter->drawRect(healthBarRect);
    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    // 绘制敌人
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

void Enemy::move()
{
    if (!m_active)
        return;
    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        // 敌人抵达了一个航点
        if (m_destinationWayPoint->nextWayPoint())
        {
            // 还有下一个航点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            // 表示进入基地
            m_game->getHpDamage(1);
            m_game->removeEnemy(this);
            return;
        }
    }
    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = m_destinationWayPoint->pos();
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值
    // 向量标准化
    double movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;
    // 确定敌人选择方向
    // 默认图片向左,需要修正180度转右
    m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x()));
}

void Enemy::doActivate()
{
    m_active = true;
}
