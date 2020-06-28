#include "chooselevelscene.h"
#include "ui_chooselevelscene.h"
#include <mainwindow.h>

chooselevelscene::chooselevelscene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooselevelscene)
{
    ui->setupUi(this);
    this->setFixedSize(1280,768);
    setWindowIcon(QIcon("://images/2.jpg"));
    setWindowTitle("选择关卡难度");
    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "//chooselevelscene.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    m_audioPlayer->startBGM();
}

chooselevelscene::~chooselevelscene()
{
    delete ui;
}

void chooselevelscene::paintEvent(QPaintEvent *)
{    QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing, true);
      painter.drawPixmap(0,0,1280,768, QPixmap("://images/chooselevelscene.jpg"));
}

void chooselevelscene::on_pushButton_clicked()
{
    Easy*d=new Easy();
    m_audioPlayer->stopBGM();
    this->hide();
    d->show();

}

void chooselevelscene::on_pushButton_2_clicked()
{
    Hard*d=new Hard();
     m_audioPlayer->stopBGM();
    this->hide();
    d->show();
}

void chooselevelscene::on_pushButton_3_clicked()
{
    m_audioPlayer->stopBGM();
    MainWindow*d=new MainWindow();
    this->hide();
    d->show();
}
