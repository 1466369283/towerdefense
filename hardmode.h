#ifndef HARDMODE_H
#define HARDMODE_H

#include <QDialog>
#include <QPainter>
#include <QPaintEvent>

namespace Ui {
class HardMode;
}

class HardMode : public QDialog
{
    Q_OBJECT
public:
    explicit HardMode(QWidget *parent = nullptr);
    ~HardMode();
    void paintEvent(QPaintEvent *);

private:
    Ui::HardMode *ui;
};

#endif // HARDMODE_H
