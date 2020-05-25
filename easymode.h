#ifndef EASYMODE_H
#define EASYMODE_H
//#pragma once

#include <QDialog>
#include <QMovie>
#include <QTimer>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QKeyEvent>
#include <waypoint.h>
#include <enemy.h>
#include <tower.h>
#include <QPaintEvent>
#include <QPainter>
#include <QList>
#include <QtGlobal>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QtDebug>




#include "towerposition.h"



class Bullet;
class TowerPosition;


namespace Ui {
class EasyMode;
}

class EasyMode : public QDialog
{
   Q_OBJECT
public:
    explicit EasyMode(QWidget *parent = nullptr);
    ~EasyMode();
    void paintEvent(QPaintEvent *);
    void loadTowerPositions();
   QList<TowerPosition> m_towerPositionsList;
   QList<Tower *> m_towersList;
   bool CanBuyTower() const;
   void mousePressEvent(QMouseEvent *event);
   QList<WayPoint *> m_wayPointsList;	// 在paintEvent中需要进行绘制，那个类似的foreach(xxx) xxx.draw(xxx)
   void addWayPoints();			// 在构造函数中调用
   void getHpDamage(int Damage);
   void removeEnemy(Enemy *enemy);
   QList<Enemy *> m_enemyList;

public slots:
   void updateMap();

private:
    Ui::EasyMode *ui;
    int m_waves;
    bool m_gameWin;
    bool loadWave();


};

#endif // EASYMODE_H
