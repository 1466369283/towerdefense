#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QDialog>
#include <QPainter>
#include <QPaintEvent>
#include <easymode.h>
#include <easy.h>
#include <hard.h>

class MainWindow;

namespace Ui {
class chooselevelscene;
}

class chooselevelscene : public QDialog
{
    Q_OBJECT
public:
    explicit chooselevelscene(QWidget *parent = nullptr);
    ~chooselevelscene();
    AudioPlayer *		    m_audioPlayer;
    void paintEvent(QPaintEvent *);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
private:
    Ui::chooselevelscene *ui;
};

#endif // CHOOSELEVELSCENE_H
