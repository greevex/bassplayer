#ifndef VIS_H
#define VIS_H

#include "config.h"
#include "bass.h"

#include <QDialog>
#include <QTimer>
#include <QPainter>
#include <QLibrary>
#include <QList>
#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>

typedef struct{
    QString version;
    QString autor;
    QString name;
    int ver;
} VisInfo;

typedef void (*Drawer)(QPainter&, float*);
typedef void (*VisInf)(VisInfo*);

typedef void (*INIT)(QWidget*);
typedef void (*UPDATE)(float *fft);
typedef void (*STOP)();

class Vis : public QDialog {
    Q_OBJECT
public:
    Vis(QWidget *parent = 0);
    ~Vis();
    void setChannel(HSTREAM chan);
    void save();

protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);

private:
    QTimer *timer;
    HSTREAM chan;
    float fft[4096];
    QLibrary *vislib;
    int ctype;
    int curr;
    void checkLibs();
    void createActions();
    void load();
    void load(QString dll);
    void unload();
    void setTitle();
    UPDATE Upd;
    Drawer Draw;
    QStringList *libs;
    QList<VisInfo*> *libsinfo;
    QList<QAction*> *actions;
private slots:
    void changeVis();
    void about();
    void toggleFullScreen();
};

#endif // VIS_H
