#ifndef HARD_H
#define HARD_H

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

class Hard : public EasyMode
{
    Q_OBJECT
public:
    explicit Hard(QWidget* parent = nullptr);
    ~Hard();
    virtual void removedEnemy(Enemy *enemy);
protected:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
private:
    QMovie* background = new QMovie("://images/hardmap.jpg");
    QPushButton* exit = new QPushButton(this);
    QMovie* station = new QMovie("//images/towerbase2.png");
    void uiSetup();
private:
    bool loadWave();
    void loadTowerPositions();
    void addWayPoints();
    void preLoadWavesInfo();
    void drawWave();
    void drawHP();
    void drawPlayerGold();
    void drawDangao();
    bool canBuyTower() const;
private:
    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList;
    QList<WayPoint *>		m_wayPointsList;
private slots:
    void gameStart();
    void updateMap();
    void leave();
    void onTimer();
};

#endif // HARD_H
