#include "waypoint.h"
#include <QPainter>
#include <QColor>

WayPoint::WayPoint(QPoint pos)
    : m_pos(pos)
    , m_nextWayPoint(nullptr)
{
}

const QPoint WayPoint::pos() const
{
    return m_pos;
}

void WayPoint::setNextWayPoint(WayPoint *nextPoint)
{
    m_nextWayPoint = nextPoint;
}

WayPoint* WayPoint::nextWayPoint() const
{
    return m_nextWayPoint;
}
