#ifndef EQ_H
#define EQ_H

#include <QDialog>
#include <QContextMenuEvent>
#include <QMenu>
#include <QSlider>
#include "bass.h"
#include "config.h"

namespace Ui {
    class Eq;
}

class Eq : public QDialog {
    Q_OBJECT
public:
    Eq(QWidget *parent = 0);
    ~Eq();
    void setEq();
    int getEq(int Hz);
    void setEq(int Hz, int value);
    float getGain(int val);

protected:
    void changeEvent(QEvent *e);
    void contextMenuEvent(QContextMenuEvent *event);

private:
    Ui::Eq *ui;
    void setTt(QSlider *slider, int hz);
    QAction *resetAction;
public:
    HFX e80;
    HFX e120;
    HFX e150;
    HFX e200;
    HFX e250;
    HFX e300;
    HFX e400;
    HFX e500;
    HFX e600;
    HFX e700;
    HFX e800;
    HFX e900;
    HFX e1000;
    HFX e2000;
    HFX e3000;
    HFX e4000;
    HFX e5000;
    HFX e6000;
    HFX e7000;
    HFX e8000;
    HFX e9000;
    HFX e10000;
    HFX e11000;
    HFX e12000;
    HFX e13000;
    HFX e14000;
    HFX e15000;
    HFX e16000;
private slots:
    void setEQ();
    void reset();
};

#endif // EQ_H
