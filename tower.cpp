#include "tower.h"
#include <QPaintEvent>
#include <QPainter>

const QSize Tower::ms_fixedSize(107, 95);


void Tower::draw(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::white);
    // 绘制攻击范围
    painter->drawEllipse(m_pos, m_AttackRange, m_AttackRange);
    // 绘制偏转坐标,由中心+偏移=左上
    // 尺寸大小派上用场了,当然也可以直接获取图片大小,是一样的
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    // 绘制炮塔并选择炮塔
    // 这里将坐标原点移到m_pos,绘制的适合,就要加上那个偏移点到左上角
    painter->translate(m_pos);
    painter->drawPixmap(offsetPoint, m_sprite);

    painter->restore();
}
