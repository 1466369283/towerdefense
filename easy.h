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
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
private:
    QMovie* background = new QMovie("://images/easymap.jpg");
    QMovie* station = new QMovie("//images/towerbase1.png");
    void uiSetup();
    QPushButton* exit = new QPushButton(this);
private:
    void preLoadWavesInfo();
    void loadTowerPositions();
    bool loadWave();
    void drawWave();
    void drawHP();
    void drawPlayerGold();
    void drawDangao();
    bool canBuyTower() const;
    void addWayPoints();
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

#endif // EASY_H
