#ifndef TCARD_H
#define TCARD_H

#include <QLabel>
#include <QMovie>
#include <QSound>
#include <QMouseEvent>


class Easy;
class EasyMode;
class Hard;

class EasyMode;
class Easy;

class tCard : public QLabel
{
public:
    tCard(QLabel* parent = nullptr);
    ~tCard();
};

class tNormalTowerCard : public tCard
{
public:
    tNormalTowerCard(QLabel* parent = nullptr);
    ~tNormalTowerCard();
private:
    QMovie* anim = new QMovie("://images/tower1xiao.png");
};


class tFireTowerCard : public tCard
{
public:
    tFireTowerCard(QLabel* parent = nullptr);
    ~tFireTowerCard();
private:
    QMovie* anim = new QMovie("://images/tower2xiao.png");
};

class tIceTowerCard : public tCard
{
public:
    tIceTowerCard(QLabel* parent = nullptr);
    ~tIceTowerCard();
private:
    QMovie* anim = new QMovie("://images/tower3xiao.png");
};


#endif // TCARD_H
