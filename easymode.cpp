#include "easymode.h"
#include <QMediaPlayer>
#include"tcard.h"

EasyMode::EasyMode(QWidget *parent) : QLabel(parent)
  , m_waves(0)
  , m_gameEnded(false)
  , m_gameWin(false)
  , m_playerHp(15)
  , m_playerGold(500)
{
    this->setMouseTracking(true);
    this->grabKeyboard();
}

void EasyMode::FireIceattack()
{
    foreach(Enemy *enemy, m_enemyList){
        if (enemy->fire != 0){
            enemy->fire--;
            enemy->getFireDamage(enemy->fireattack);
        }
        if(enemy->ice != 0){
            enemy->ice--;
            if (enemy->ice == 0)
            {
                enemy->m_walkingSpeed = enemy->m_normalSpeed;
                enemy->m_slowSpeed = enemy->m_normalSpeed;
            }
            else
            {
                enemy->m_walkingSpeed = enemy->m_slowSpeed;
            }
        }
    }
}

QList<Enemy *> EasyMode::enemyList() const
{
    return m_enemyList;
}

void EasyMode::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

void EasyMode::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void EasyMode::awardGold(int gold)
{
    m_playerGold += gold;
    update();
}

void EasyMode::getHpDamage(int damage)
{
    m_audioPlayer->playSound(LifeLoseSound);
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

AudioPlayer *EasyMode::audioPlayer() const
{
    return m_audioPlayer;
}

void EasyMode::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;

        m_audioPlayer->stopBGM();
        m_audioPlayer->playLoseSound();
    }
}

EasyMode::~EasyMode()
{
    if (!(this->MoneyFront == nullptr)) delete this->MoneyFront;
    if (!(this->MoneyBar == nullptr)) delete this->MoneyBar;
    if (!(this->moneybar == nullptr))delete this->moneybar;
    if (!(this->MoneyLabel == nullptr)) delete this->MoneyLabel;
    if (!(this->moneylabel == nullptr)) delete this->moneylabel;
    if (!(this->LifeFront == nullptr))delete this->LifeFront;
    if (!(this->LifeBar == nullptr)) delete this->LifeBar;
    if (!(this->lifebar == nullptr)) delete this->lifebar;
    if (!(this->LifeLabel == nullptr))delete this->LifeLabel;
    if (!(this->lifelabel == nullptr)) delete this->lifelabel;
    if (!(this->WaveFront == nullptr)) delete this->WaveFront;
    if (!(this->WaveBar == nullptr))delete this->WaveBar;
    if (!(this->wavebar == nullptr)) delete this->wavebar;
    if (!(this->WaveLabel == nullptr)) delete this->WaveLabel;
    if (!(this->wavelabel == nullptr))delete this->wavelabel;
    if (!(this->LevelUp == nullptr)) delete this->LevelUp;
    if (!(this->levelup == nullptr)) delete this->levelup;
    if (!(this->LevelFront == nullptr)) delete this->LevelFront;
    if (!(this->levelbar == nullptr)) delete this->levelbar;
    if (!(this->LevelBar == nullptr)) delete this->LevelBar;
    if (!(this->Upgrade_MoneyFront == nullptr))delete this->Upgrade_MoneyFront;
    if (!(this->upgrade_moneybar == nullptr))delete this->upgrade_moneybar;
    if (!(this->Upgrade_MoneyBar == nullptr))delete this->Upgrade_MoneyBar;
    delete Base;
    delete base;
    delete NormalTowerPic;
    delete normalTowerPic;
    delete FireTowerPic;
    delete fireTowerPic;
    delete IceTowerPic;
    delete iceTowerPic;
    delete currentCard;
}

void EasyMode::mouseMoveEvent(QMouseEvent *event)
{
    m = event->pos();
    if (this->currentCard != nullptr)
    {
        this->currentCard->move(m + QPoint(-40, 1));
    }
}
