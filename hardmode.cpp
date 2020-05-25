#include "hardmode.h"
#include "ui_hardmode.h"
#include "mainwindow.h"

HardMode::HardMode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HardMode)
{
    ui->setupUi(this);
    this->setFixedSize(1280,768);
    setWindowIcon(QIcon("://images/2.jpg"));  //设置图标
    setWindowTitle("困难模式");
}

void HardMode::paintEvent(QPaintEvent *)
{    QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing, true);
      painter.drawPixmap(0,0,1280,768, QPixmap("://images/hardmap.png"));
}

HardMode::~HardMode()
{
    delete ui;
}
