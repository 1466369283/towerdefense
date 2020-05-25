#ifndef TOWER_H
#define TOWER_H
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QPainter>


class Tower
{
public:
    Tower(QPoint center_pos,QPixmap sprite=QPixmap("://images/normaltower.png"),int AttackRange=140,int Damage=20,int FireRate=1000):
        m_pos(center_pos),
        m_sprite(sprite),
        m_AttackRange(AttackRange),
        m_Damage(Damage),
        m_FireRate(FireRate){}
    void draw(QPainter *painter);
    static const QSize ms_fixedSize;
private:
    QPoint m_pos;
    QPixmap m_sprite;
    int m_AttackRange;
    int m_Damage;
    int m_FireRate;
};

#endif // TOWER_H
