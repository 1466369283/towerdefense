#ifndef EASY_H
#define EASY_H

#include <QWidget>
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


#include "bullet.h"
#include "audioplayer.h"
#include "towerposition.h"
#include "plistreader.h"
#include <easymode.h>

class tCard;

class Easy : public EasyMode
{
    Q_OBJECT
public:
    explicit Easy(QWidget* parent = nullptr);
    ~Easy();
    virtual void removedEnemy(Enemy *enemy);

protected:

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QMovie* background = new QMovie("://images/easymap.jpg");
    QPushButton* exit = new QPushButton(this);
    QMovie* station = new QMovie("//images/towerbase1.png");

    //QPoint cell;
    void uiSetup();

    //增加代码 6-6
private:
    void loadTowerPositions();
    void addWayPoints();
    bool loadWave();
    bool canBuyTower() const;
    void drawWave();
    void drawHP();
    void drawPlayerGold();
    //void doGameOver();
    void preLoadWavesInfo();
    void drawDangao();

private:
    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList; //√
    QList<WayPoint *>		m_wayPointsList;

private slots:
    void onTimer();
    void updateMap(); //原来的槽
    void gameStart(); //原来的槽
    void leave();

};
#endif // EASY_H
