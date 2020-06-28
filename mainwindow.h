#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <chooselevelscene.h>

class chooselevelscene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    AudioPlayer *		    m_audioPlayer;
    void paintEvent(QPaintEvent *);
private slots:
    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
