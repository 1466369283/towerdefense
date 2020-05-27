#include "easymode.h"
#include "ui_easymode.h"
#include <mainwindow.h>
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <audioplayer.h>
#include <plistreader.h>

static const int TowerCost = 300;

EasyMode::EasyMode(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EasyMode)
    , m_waves(0)
    , m_playerHp(5)
    , m_playrGold(1000)
    , m_gameEnded(false)
    , m_gameWin(false)
{
    ui->setupUi(this);
    setFixedSize(1280,768);
    preLoadWavesInfo();
    loadTowerPositions();
    addWayPoints();

    m_audioPlayer = new AudioPlayer(this);
    m_audioPlayer->startBGM();


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(10);

    // 设置300ms后游戏启动
    QTimer::singleShot(300, this, SLOT(gameStart()));
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

void EasyMode::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
     painter.drawPixmap(0,0,1280,768, QPixmap("://images/easymap.jpg"));
    if (m_gameEnded || m_gameWin)
    {
        QString text = m_gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }

    foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&painter);

    foreach (const Tower *tower, m_towersList)
        tower->draw(&painter);

    //foreach (const WayPoint *wayPoint, m_wayPointsList)
    //    wayPoint->draw(&painter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&painter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&painter);

    drawHP(&painter);
    drawPlayerGold(&painter);

}

void EasyMode::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            m_audioPlayer->playSound(TowerPlaceSound);
            m_playrGold -= TowerCost;
            it->setHasTower();

            Tower *tower = new Tower(it->centerPos(), this);
            m_towersList.push_back(tower);
            update();
            break;
        }

        ++it;
    }
}

bool EasyMode::canBuyTower() const
{
    if (m_playrGold >= TowerCost)
        return true;
    return false;
}

void EasyMode::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(400, 5, 100, 25), QString("WAVE : %1").arg(m_waves + 1));
}

void EasyMode::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(m_playerHp));
}

void EasyMode::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(200, 5, 200, 25), QString("GOLD : %1").arg(m_playrGold));
}

void EasyMode::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

void EasyMode::awardGold(int gold)
{
    m_playrGold += gold;
    update();
}

AudioPlayer *EasyMode::audioPlayer() const
{
    return m_audioPlayer;
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


void EasyMode::getHpDamage(int damage/* = 1*/)
{
    m_audioPlayer->playSound(LifeLoseSound);
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void EasyMode::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
            m_gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}

void EasyMode::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void EasyMode::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

void EasyMode::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}

void EasyMode::preLoadWavesInfo()
{
    QFile file(":/config/Waves.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    // 获取波数信息
    m_wavesInfo = reader.data();

    file.close();
}

bool EasyMode::loadWave()
{
    if (m_waves >= m_wavesInfo.size())
        return false;

    WayPoint *startWayPoint = m_wayPointsList.back();
    QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();

        Enemy *enemy = new Enemy(startWayPoint, this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
    }

    return true;
}


QList<Enemy *> EasyMode::enemyList() const
{
    return m_enemyList;
}

void EasyMode::gameStart()
{
    loadWave();
}
