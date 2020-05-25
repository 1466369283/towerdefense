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
    setWindowIcon(QIcon("://images/2.jpg"));  //设置图标
    setWindowTitle("刘希的塔防游戏");


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(0,0,1280,768, QPixmap("://images/background1.png"));


}

void MainWindow::on_pushButton_clicked()
{
    chooselevelscene* d=new chooselevelscene();
    this->hide();
    d->show();
}
