#include "tCard.h"
#include "easymode.h"
#include "easy.h"
#include "hard.h"

tCard::tCard(QLabel* parent) : QLabel(parent)
{
    this->setCursor(Qt::PointingHandCursor);
}

tCard::~tCard()
{

}

tNormalTowerCard::tNormalTowerCard(QLabel *parent):tCard(parent)
{
    this->setMovie(anim);
    anim->start();

}

tNormalTowerCard::~tNormalTowerCard()
{
    delete this->anim;
}

tFireTowerCard::tFireTowerCard(QLabel *parent):tCard(parent)
{
    this->setMovie(anim);
    anim->start();
}

tFireTowerCard::~tFireTowerCard()
{
    delete this->anim;
}

tIceTowerCard::tIceTowerCard(QLabel *parent):tCard(parent)
{
    this->setMovie(anim);
    anim->start();
}

tIceTowerCard::~tIceTowerCard()
{
    delete this->anim;
}


