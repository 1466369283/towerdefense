#include "easymode.h"
#include "ui_easymode.h"
#include "mainwindow.h"
#include <towerposition.h>
#include <iostream>
#include <waypoint.h>
#include <QTimer>
#include <enemy.h>
using namespace  std;


EasyMode::EasyMode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EasyMode)
{
    ui->setupUi(this);
    this->setFixedSize(1280,768);
    setWindowIcon(QIcon("://images/2.jpg"));  //设置图标
    setWindowTitle("简单模式");
    m_waves=0;
    loadTowerPositions();
    addWayPoints();
    loadWave();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(10);

}

void EasyMode::paintEvent(QPaintEvent *)
{    QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing, true);
      painter.drawPixmap(0,0,1280,768, QPixmap("://images/easymap.jpg"));
       int i;
         for(i=0;i<=12;++i)
         {
             painter.drawPixmap(m_towerPositionsList[i].zuoshangjiao(),QPixmap("://images/towerbase.png"));
         }
          foreach (Tower *tower, m_towersList)
              tower->draw(&painter);//画塔
           foreach (WayPoint *waypoint, m_wayPointsList)
               waypoint->draw(&painter);//画路线
            foreach (Enemy *enemy, m_enemyList)
                enemy->draw(&painter);//画敌人

}

EasyMode::~EasyMode()
{
    delete ui;
}

void EasyMode::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(199, 264),
        QPoint(305, 264),
        QPoint(412, 264),
        QPoint(950, 279),
        QPoint(950, 384),
        QPoint(625, 358),
        QPoint(733, 359),
        QPoint(733, 468),
        QPoint(626, 468),
        QPoint(518, 468),
        QPoint(411, 468),
        QPoint(304, 468),
        QPoint(198, 468)
    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
        m_towerPositionsList.push_back(pos[i]);
}

void EasyMode::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (CanBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            it->setHasTower();
            Tower *tower = new Tower(it->centerPos());
            m_towersList.push_back(tower);
            update();
            break;
        }

        ++it;
    }
}

bool EasyMode::CanBuyTower() const
{
    return true;
}


void EasyMode::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(1108, 530));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(1108, 203));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(119, 203));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(119, 399));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(564, 399));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(564, 302));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(889, 302));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(889, 604));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(126, 604));
    m_wayPointsList.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);
}

void EasyMode::getHpDamage(int Damage/* = 1*/)
{

    // 暂时空实现，以后这里进行基地费血行为
}

void EasyMode::removeEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    m_enemyList.removeOne(enemy);
    delete enemy;
    if (m_enemyList.empty())
    {
        ++m_waves; // 当前波数加1
        // 继续读取下一波
        if (!loadWave())
        {
            // 当没有下一波时，这里表示游戏胜利
            // 设置游戏胜利标志为true
            m_gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}

bool EasyMode::loadWave()
{
    if (m_waves >= 6)
        return false;
    WayPoint *startWayPoint = m_wayPointsList.back(); // 这里是个逆序的，尾部才是其实节点
    int enemyStartInterval[] = {100,500,600,1000,3000,6000};
    for (int i = 0; i < 6; ++i)
    {
        Enemy *enemy = new Enemy(startWayPoint,this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
    }
    return true;
}

void EasyMode::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    update();
}
