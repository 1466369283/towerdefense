#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPushButton>
#include <chooselevelscene.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1280,768);
    setWindowIcon(QIcon("://images/icon.jpg"));
    setWindowTitle("古古怪怪大作战");
    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "//mainwindow.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    m_audioPlayer->startBGM();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(0,0,1280,768, QPixmap("://images/menu.jpg"));
}

void MainWindow::on_pushButton_clicked()
{
    chooselevelscene* d=new chooselevelscene();
    m_audioPlayer->stopBGM();
    this->hide();
    d->show();
}
