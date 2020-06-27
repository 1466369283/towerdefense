#include "easy.h"
#include "ui_easy.h"
#include <QLabel>
#include "tcard.h"
#include "easymode.h"
#include <mainwindow.h>

static const int TowerCost = 150;

Easy::Easy(QWidget* parent)
    : EasyMode (parent)
{
    this->setFixedSize(1280,768);
    setWindowIcon(QIcon("://images/icon.jpg"));  //设置图标
    setWindowTitle("简单模式");
    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "//easymap.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    m_audioPlayer->startBGM();
    this->setMovie(this->background);
    this->background->start();
    this->show();

    preLoadWavesInfo(); //设置波数
    loadTowerPositions(); //调用位置函数
    addWayPoints();

    QTimer *Firetime = new QTimer(this);
    connect(Firetime, SIGNAL(timeout()), this, SLOT(FireIceattack()));
    Firetime->start(100);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);
    this->uiSetup();

    QTimer::singleShot(500, this, SLOT(gameStart()));
}

void Easy::uiSetup()
{
    MoneyBar->setGeometry(220, 615, 300, 200);
    moneybar->start();
    MoneyBar->show();
    MoneyBar->setMovie(moneybar);
    MoneyFront->setGeometry(220-55, 685, 300, 200);
    MoneyFront->setFont(QFont("等线", 17));
    MoneyFront->setText("50");
    MoneyFront->setAlignment(Qt::AlignHCenter);
    MoneyFront->show();
    MoneyFront->raise();
    MoneyLabel->setGeometry(220-80, 615, 300, 200);
    moneylabel->start();
    MoneyLabel->show();
    MoneyLabel->setMovie(moneylabel);

    LifeBar->setGeometry(500,615, 300, 200);
    lifebar->start();
    LifeBar->show();
    LifeBar->setMovie(lifebar);
    LifeFront->setGeometry(500-55, 685, 300, 200);
    LifeFront->setFont(QFont("等线", 17));
    LifeFront->setText("10");
    LifeFront->setAlignment(Qt::AlignHCenter);
    LifeFront->show();
    LifeFront->raise();
    LifeLabel->setGeometry(500-80, 615, 300, 200);
    lifelabel->start();
    LifeLabel->show();
    LifeLabel->setMovie(lifelabel);

    WaveBar->setGeometry(780, 615, 300, 200);
    wavebar->start();
    WaveBar->show();
    WaveBar->setMovie(wavebar);
    WaveFront->setGeometry(780-55, 685, 300, 200);
    WaveFront->setFont(QFont("等线", 17));
    WaveFront->setText("1");
    WaveFront->setAlignment(Qt::AlignHCenter);
    WaveFront->show();
    WaveFront->raise();
    WaveLabel->setGeometry(780-80, 615, 300, 200);
    wavelabel->start();
    WaveLabel->show();
    WaveLabel->setMovie(wavelabel);

    Base->setGeometry(685, 35, 228, 306);
    base->start();
    Base->show();
    Base->setMovie(base);
    Base->raise();

    LevelUp->setGeometry(150, 20, 100, 100);
    levelup->start();
    LevelUp->show();
    LevelUp->setMovie(levelup);
    LevelUp->raise();

    LevelBar->setGeometry(150-90, -30, 300, 200);
    levelbar->start();
    LevelBar->show();
    LevelBar->setMovie(levelbar);
    LevelBar->raise();
    LevelFront->setGeometry(-41, 45, 300, 200);
    LevelFront->setFont(QFont("等线", 17));
    LevelFront->setStyleSheet("background-color: transparent;font-size:30px;color:white");
    LevelFront->setAlignment(Qt::AlignHCenter);
    LevelFront->show();
    LevelFront->raise();

    Upgrade_MoneyBar->setGeometry(150+90, -30, 300, 200);
    upgrade_moneybar->start();
    Upgrade_MoneyBar->show();
    Upgrade_MoneyBar->setMovie(upgrade_moneybar);
    Upgrade_MoneyBar->raise();

    Upgrade_MoneyFront->setGeometry(139, 45, 300, 200);
    Upgrade_MoneyFront->setFont(QFont("等线", 17));
    Upgrade_MoneyFront->setStyleSheet("background-color: transparent;font-size:30px;color:yellow");
    Upgrade_MoneyFront->setAlignment(Qt::AlignHCenter);
    Upgrade_MoneyFront->show();
    Upgrade_MoneyFront->raise();//记得delete！！！

    exit->setGeometry(1150,20, 100, 100); //设置退出按钮
    exit->setFlat(true);
    exit->setIcon(QIcon("://images/leave.png"));
    exit->setIconSize(QSize(100,100));
    exit->setStyleSheet("background: transparent");
    exit->setCursor(Qt::PointingHandCursor);
    connect(exit, SIGNAL(clicked()), this, SLOT(leave()));
    exit->show();
    exit->raise();

    NormalTowerPic->setFixedSize(70,140);
    NormalTowerPic->setGeometry(586-200, 0,70, 140);
    normalTowerPic->start();
    NormalTowerPic->show();
    NormalTowerPic->setMovie(normalTowerPic);

    FireTowerPic->setFixedSize(70,140);
    FireTowerPic->setGeometry(586, 0 , 70, 140);
    fireTowerPic->start();
    FireTowerPic->show();
    FireTowerPic->setMovie(fireTowerPic);

    IceTowerPic->setFixedSize(70,140);
    IceTowerPic->setGeometry(586+200, 0 , 70, 140);
    iceTowerPic->start();
    IceTowerPic->show();
    IceTowerPic->setMovie(iceTowerPic);

    tCard *card0 = new tNormalTowerCard(this);
    card0->setGeometry(586-200,0,70,140);
    Cards.append(card0);
    card0->show();

    Front1 = new QLabel(this);
    Front1->setStyleSheet("background-color: transparent;font-size:30px;color:green");
    Front1->setText("150金币");
    Front1->setGeometry(586-200-35, 70 , 300, 300);
    Front1->setAlignment(Qt::AlignHCenter); //居中对齐
    Front1->setFont(QFont("等线", 17));
    Front1->show();
    Front1->raise();

    tCard *card1 = new tFireTowerCard(this);
    card1->setGeometry(586, 0 , 70, 140);
    Cards.append(card1);
    card1->show();

    Front2 = new QLabel(this);
    Front2->setStyleSheet("background-color: transparent;font-size:30px;color:red");
    Front2->setText("150金币");
    Front2->setGeometry(586-35, 70 , 300, 300);
    Front2->setAlignment(Qt::AlignHCenter);
    Front2->setFont(QFont("等线", 17));
    Front2->show();
    Front2->raise();

    tCard *card2 = new tIceTowerCard(this);
    card2->setGeometry(586+200, 0 , 70, 140);
    Cards.append(card2);
    card2->show();

    Front3 = new QLabel(this);
    Front3->setStyleSheet("background-color: transparent;font-size:30px;color:blue");
    Front3->setText("150金币");
    Front3->setGeometry(586+200-35, 70 , 300, 300);
    Front3->setAlignment(Qt::AlignHCenter);
    Front3->setFont(QFont("等线", 17));
    Front3->show();
    Front3->raise();

}

void Easy::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    if(enemy!=nullptr)
    {m_enemyList.removeOne(enemy);

    delete enemy;}

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
        m_gameWin = true;
        m_audioPlayer->stopBGM();
        m_audioPlayer->playWinSound();
        // 游戏胜利转到游戏胜利场景
        // 这里暂时以打印处理
        }
    }
}


void Easy::loadTowerPositions()
{
    QPoint pos[] =
    {
                QPoint(88 ,274),
                QPoint(189,274),
                QPoint(297,274),
                QPoint(401,274),
                QPoint(641,202),
                QPoint(641,290),
                QPoint(641,386),
                QPoint(641,479),
                QPoint(747,479),
                QPoint(846,479),
                QPoint(954,479)


    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
        m_towerPositionsList.push_back(pos[i]);
}

void Easy::addWayPoints()
{
    //敌人航点【可改】
        int x=26;
        WayPoint *wayPoint1 = new WayPoint(QPoint(1197+x, 628));
        m_wayPointsList.push_back(wayPoint1);

        WayPoint *wayPoint2 = new WayPoint(QPoint(584+x, 628));
        m_wayPointsList.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);

        WayPoint *wayPoint3 = new WayPoint(QPoint(584+x, 233));
        m_wayPointsList.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);

        WayPoint *wayPoint4 = new WayPoint(QPoint(79+x, 233));
        m_wayPointsList.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);
}

bool Easy::loadWave()
{
    if (m_waves >= m_wavesInfo.size())
        return false;

    WayPoint *startWayPoint = m_wayPointsList.back();
    QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();

        Enemy *enemy;
        int j=i%4;
        switch(j){
        case 0:
            enemy = new normalEnemy(startWayPoint, this);
            break;
        case 1:
            enemy=new iceEnemy(startWayPoint, this);
            break;
        case 2:
            enemy=new fireEnemy(startWayPoint, this);
            break;
        case 3:
            enemy=new bossEnemy(startWayPoint, this);
            break;
        }
        m_enemyList.push_back(enemy);
        QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
    }

    return true;
}

bool Easy::canBuyTower() const
{
    if (m_playerGold >= TowerCost)
        return true;
    return false;
}

void Easy::drawWave()
{
    WaveFront->setText(QString("第%1波敌人").arg(m_waves +1));
    WaveFront->setAlignment(Qt::AlignHCenter);
    WaveFront->show();
    WaveFront->raise();
}

void Easy::drawHP()
{
    LifeFront->setText(QString("血量%1").arg(m_playerHp));
    LifeFront->setAlignment(Qt::AlignHCenter);
    LifeFront->show();
    LifeFront->raise();
}

void Easy::drawPlayerGold()
{
    MoneyFront->setText(QString("%1金币").arg(m_playerGold));
    MoneyFront->setAlignment(Qt::AlignHCenter);
    MoneyFront->show();
    MoneyFront->raise();
}

void Easy::drawDangao()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(1140, 560,100, 100, QPixmap("://images/dangao.png"));
}

void Easy::preLoadWavesInfo()
{
    QFile file("://config/Waves.plist");
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

Easy::~Easy()
{
    delete this->background;
    delete this->exit;

    foreach (tCard *card, Cards)
    {
        Q_ASSERT(card);
        Cards.removeOne(card);
        delete card;
    }

    foreach (Tower *tower, m_towersList)
    {
        Q_ASSERT(tower);
        m_towersList.removeOne(tower);
        delete tower;
    }
    foreach (Enemy *enemy, m_enemyList)
    {
        Q_ASSERT(enemy);
        m_enemyList.removeOne(enemy);
        delete enemy;
    }
    foreach (Bullet *bullet, m_bulletList)
    {
        removedBullet(bullet);
    }
    delete Front1;
    delete Front2;
    delete Front3;
    delete Front4;

    //delete ui;
}

void Easy::paintEvent(QPaintEvent *)
{
    if (m_gameEnded || m_gameWin)
    {
        MoneyFront->hide();
        MoneyBar->hide();
        MoneyLabel->hide();
        LifeFront->hide();
        LifeBar->hide();
        LifeLabel->hide();
        WaveFront->hide();
        WaveBar->hide();
        WaveLabel->hide();
        Base->hide();
        Front1->hide();
        Front2->hide();
        Front3->hide();
        Front4->hide();
        LevelUp->hide();
        LevelFront->hide();
        LevelBar->hide();
        Upgrade_MoneyFront->hide();
        Upgrade_MoneyBar->hide();

        NormalTowerPic->hide();
        FireTowerPic->hide();
        IceTowerPic->hide();

        foreach (tCard *card, Cards)
        {
            Q_ASSERT(card);
            Cards.removeOne(card);
            delete card;
        }

        foreach (Tower *tower, m_towersList)
        {
            Q_ASSERT(tower);
            m_towersList.removeOne(tower);
            delete tower;
        }
        foreach (Enemy *enemy, m_enemyList)
        {
            Q_ASSERT(enemy);
            m_enemyList.removeOne(enemy);
            delete enemy;
        }
        foreach (Bullet *bullet, m_bulletList)
        {
            removedBullet(bullet);
        }

        if(m_gameWin){
        QPixmap loseScene("://images/victory.jpg");
        QPainter painter(this);
        painter.drawPixmap(0, 0, loseScene);
        //audioPlayer()->playWinSound();

        }

        if(m_gameEnded)
        {
            QPixmap loseScene("://images/lose.jpg");
            QPainter painter(this);
            painter.drawPixmap(0, 0, loseScene);
        }
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawPixmap(0,0,1280,768, QPixmap("://images/easymap.jpg"));
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
    drawWave();
    drawHP();
    drawPlayerGold();
    drawDangao();
}

void Easy::mousePressEvent(QMouseEvent * event)
{
    //单击鼠标后的处理
    QPoint pressPos = event->pos();
    int posx = pressPos.x();
    int posy = pressPos.y();

    if (upgradestate)
    {
        if (posx >= 150 && posx <= 150+100 && posy >= 20 && posy <= 20+100 && currenttower->m_level != 5)
        {
            //升级
            int level = currenttower->m_level;
            int gold = level*100;
            if (m_playerGold >= gold)
            {
                m_playerGold -= gold;
                currenttower->levelup();

                LevelFront->setText(QString("level %1").arg(currenttower->m_level));
                LevelFront->show();
                LevelFront->raise();

                if (level != 4)
                    Upgrade_MoneyFront->setText(QString("%1").arg(gold+100));
                else {
                    Upgrade_MoneyFront->setText("---");
                }
                Upgrade_MoneyFront->show();
                Upgrade_MoneyFront->raise();

            }
        }

        else {
            currenttower = nullptr;
            upgradestate = 0;

            LevelFront->setText("");
            LevelFront->show();
            LevelFront->raise();

            Upgrade_MoneyFront->setText("");
            Upgrade_MoneyFront->show();
            Upgrade_MoneyFront->raise();

        }
    }
    if (currentCard == nullptr){
        auto it = m_towerPositionsList.begin();
        while (it != m_towerPositionsList.end())
        {
            if (currentCard == nullptr && it->containPoint(pressPos) && it->hasTower())
            {

                currenttower = it->m_tower;
                //有塔状态：显示等级和升级图表
                LevelFront->setText(QString("level %1").arg(it->m_tower->m_level));
                LevelFront->show();
                LevelFront->raise();
                switch (it->m_tower->m_level)
                {
                case 1:
                    Upgrade_MoneyFront->setText("100");
                    break;
                case 2:
                    Upgrade_MoneyFront->setText("200");
                    break;
                case 3:
                    Upgrade_MoneyFront->setText("300");
                    break;
                case 4:
                    Upgrade_MoneyFront->setText("400");
                    break;
                default:
                    Upgrade_MoneyFront->setText("---");
                    break;
                }
                Upgrade_MoneyFront->show();
                Upgrade_MoneyFront->raise();

                upgradestate = 1;
            }
            ++it;
        }
    }

    if(currentCard != nullptr){
        bool temp = 0;
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (currentCard != nullptr && canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            temp = 1;
            m_audioPlayer->playSound(TowerPlaceSound);

            it->setHasTower();
            Tower *tower;
            switch(currentIndex)
            {
            case 0:tower = new NormalTower(it->centerPos(), this);
                it->m_tower = tower;
                m_playerGold -= 150;
                it->m_towerkind = 0;
                break;
            case 1:tower = new FireTower(it->centerPos(), this);
                m_playerGold -= 150;
                it->m_tower = tower;
                it->m_towerkind = 1;
                break;
            case 2:tower = new IceTower(it->centerPos(), this);
                m_playerGold -= 150;
                it->m_towerkind = 2;
                it->m_tower = tower;
                break;
            }
            m_towersList.push_back(tower);
            update(); //调用paintevent(),重绘画面
            currentCard->move(currentPos);
            currentCard = nullptr;
            break;
        }

        ++it;
    }
        if(temp == 0)
        {
           currentCard->move(currentPos);
           currentCard = nullptr;
        }
    }

    //if(state == 0) //空状态
    int cardindex = -1;
    if (posx >= 586-200 && posx <= 586-200+70 && posy >= 0 && posy <= 0+140)
        cardindex = 0;
    else if (posx >= 586 && posx <= 586+70 && posy >= 0 && posy <= 0+140)
        cardindex = 1;
    else if (posx >= 586+200 && posx <= 586+200+70 && posy >= 0 && posy <= 0+140)
        cardindex = 2;

    if (cardindex >= 0)
    {
        currentPos = Cards[cardindex]->pos();
        this->currentCard = Cards[cardindex];
        currentIndex = cardindex;
    }



    if(event->button() == Qt::RightButton)
      {
        auto it=m_towerPositionsList.begin();
        while(it!=m_towerPositionsList.end())
        {
            if(it->containPoint(pressPos)&&it->hasTower())
            {
                it->setHasTower(false);
                int i;
                for(i=0;i<m_towersList.size();i++)
                {
                    if(it->containPoint(m_towersList[i]->m_pos))
                    {
                        m_towersList[i]->m_fireRateTimer->stop();
                        m_playerGold+=m_towersList[i]->m_level*100;
                        m_towersList.erase(m_towersList.begin()+i);
                        it->setHasTower(false);
                        audioPlayer()->playSound(BreakTowerSound);
                    }
                }
                update();
                break;
            }
            ++it;
        }
       }
}

void Easy::onTimer()
{
    this->exit->raise();
}

void Easy::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}

void Easy::gameStart()
{
    loadWave();
}

void Easy::leave()
{
    MainWindow *d=new MainWindow();
     m_audioPlayer->stopBGM();
    this->hide();
    d->show();
}
