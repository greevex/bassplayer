#ifndef VIS_H
#define VIS_H

#include <QDialog>
#include <QTimer>
#include "bass.h"
#include <QPainter>

namespace Ui {
    class Vis;
}

class Vis : public QDialog {
    Q_OBJECT
public:
    Vis(QWidget *parent = 0);
    ~Vis();
    void setChannel(HSTREAM chan);

protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *event);

private:
    Ui::Vis *ui;
    QTimer *timer;
    HSTREAM chan;
    float fft[2048];
    int pik[128];
};

#endif // VIS_H
