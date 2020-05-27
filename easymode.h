#ifndef EASYMODE_H
#define EASYMODE_H

#include <QDialog>
#include <QList>
#include "towerposition.h"
#include "tower.h"
#include <QMovie>
#include <QTimer>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QMediaPlayer>

namespace Ui {
class EasyMode;
}

class WayPoint;
class Enemy;
class Bullet;
class AudioPlayer;

class EasyMode : public QDialog
{
    Q_OBJECT

public:
    explicit EasyMode(QWidget *parent = nullptr);
    ~EasyMode();

    void getHpDamage(int damage = 1);
    void removedEnemy(Enemy *enemy);
    void removedBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    void awardGold(int gold);

    AudioPlayer* audioPlayer() const;
    QList<Enemy *> enemyList() const;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:
    void updateMap();
    void gameStart();

private:
    void loadTowerPositions();
    void addWayPoints();
    bool loadWave();
    bool canBuyTower() const;
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void doGameOver();
    void preLoadWavesInfo();

private:
    Ui::EasyMode *		ui;
    int						m_waves;
    int						m_playerHp;
    int						m_playrGold;
    bool					m_gameEnded;
    bool					m_gameWin;
    AudioPlayer *			m_audioPlayer;
    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList;
    QList<Tower *>			m_towersList;
    QList<WayPoint *>		m_wayPointsList;
    QList<Enemy *>			m_enemyList;
    QList<Bullet *>			m_bulletList;
};

#endif // EASYMODE_H
