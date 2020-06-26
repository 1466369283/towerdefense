#ifndef EASYMODE_H
#define EASYMODE_H

#include <QDialog>
#include <QMovie>
#include <QList>
#include <QLabel>
#include "towerposition.h"
#include "tower.h"
#include <QMovie>
#include <QPushButton>
#include <QTimer>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QMediaPlayer>
#include "tcard.h"
#include <audioplayer.h>
#include "bullet.h"
#include "enemy.h"

class WayPoint;
class Enemy;
class Bullet;
class AudioPlayer;
class tCard;
class AudioPlayer;


namespace Ui {
class EasyMode;
}

class EasyMode : public QLabel
{
    Q_OBJECT

public:
    int sunPoint = 50;
    tCard* currentCard = nullptr;
    QPoint currentPos;
    QList<tCard*> Cards;
    QPoint m;
    int currentIndex = -1;
    int upgradestate = 0;
    Tower* currenttower;


    explicit EasyMode(QWidget *parent = nullptr);
    ~EasyMode();
    void mouseMoveEvent(QMouseEvent *event);

    QTimer* timer = nullptr;

    QLabel* MoneyFront = new QLabel(this);
    QLabel* MoneyBar = new QLabel(this);
    QMovie* moneybar = new QMovie("://images/moneybar.png");
    QLabel* MoneyLabel = new QLabel(this);
    QMovie* moneylabel = new QMovie("://images/money.png");

    QLabel* LifeFront = new QLabel(this);
    QLabel* LifeBar = new QLabel(this);
    QMovie* lifebar = new QMovie("://images/lifebar.png");
    QLabel* LifeLabel = new QLabel(this);
    QMovie* lifelabel = new QMovie("://images/life.png");

    QLabel* WaveFront = new QLabel(this);
    QLabel* WaveBar = new QLabel(this);
    QMovie* wavebar = new QMovie("://images/wavebar.png");
    QLabel* WaveLabel = new QLabel(this);
    QMovie* wavelabel = new QMovie("://images/wave.png");

    QLabel* Front1 = new QLabel(this);
    QLabel* Front2 = new QLabel(this);
    QLabel* Front3 = new QLabel(this);
    QLabel* Front4 = new QLabel(this);

    QLabel* NormalTowerPic = new QLabel(this);
    QMovie* normalTowerPic = new QMovie("://images/tower1xiao.png");
    QLabel* FireTowerPic = new QLabel(this);
    QMovie* fireTowerPic = new QMovie("://images/tower2xiao.png");
    QLabel* IceTowerPic = new QLabel(this);
    QMovie* iceTowerPic = new QMovie("://images/tower3xiao.png");

    QLabel* Base = new QLabel(this);
    QMovie* base = new QMovie("://images/Luobo.png");

    QLabel* LevelUp = new QLabel(this);
    QMovie* levelup = new QMovie("://images/levelup.png");

    QLabel* LevelFront = new QLabel(this);
    QLabel* LevelBar = new QLabel(this);
    QMovie* levelbar = new QMovie("://images/info_bar.png");

    QLabel* Upgrade_MoneyFront = new QLabel(this);
    QLabel* Upgrade_MoneyBar = new QLabel(this);
    QMovie* upgrade_moneybar = new QMovie("://images/info_bar.png");

    void addBullet(Bullet *bullet);
    virtual void removedEnemy(Enemy *enemy) = 0;
    void removedBullet(Bullet *bullet);
    QList<Enemy *> enemyList() const;
    void awardGold(int gold);
    void getHpDamage(int damage);
    void doGameOver();
    AudioPlayer* audioPlayer() const;

    QList<Bullet *>			m_bulletList;
    QList<Enemy *>			m_enemyList;
    QList<Tower *>			m_towersList;
    int						m_waves;
    bool					m_gameEnded;
    bool					m_gameWin;
    int						m_playerHp;
    int						m_playerGold;
    AudioPlayer *		    m_audioPlayer;


public slots:
    void FireIceattack();


};




#endif // EASYMODE_H
