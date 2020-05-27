#include "chooselevelscene.h"
#include "ui_chooselevelscene.h"
#include <mainwindow.h>

chooselevelscene::chooselevelscene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooselevelscene)
{
    ui->setupUi(this);
    this->setFixedSize(1280,768);
    setWindowIcon(QIcon("://images/2.jpg"));  //设置图标
    setWindowTitle("选择关卡难度");
}

chooselevelscene::~chooselevelscene()
{
    delete ui;
}

void chooselevelscene::paintEvent(QPaintEvent *)
{    QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing, true);
      painter.drawPixmap(0,0,1280,768, QPixmap("://images/chooselevelscene.png"));
}

void chooselevelscene::on_pushButton_3_clicked()
{
    MainWindow*d=new MainWindow();
    this->hide();
    d->show();
}

void chooselevelscene::on_pushButton_clicked()
{
    EasyMode*d=new EasyMode();
    this->hide();
    d->show();

}

void chooselevelscene::on_pushButton_2_clicked()
{
    HardMode*d=new HardMode();
    this->hide();
    d->show();
}
