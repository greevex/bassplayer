#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTimer>
#include "bass.h"
#include "eq.h"
#include "pl.h"
#include "vis.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *conftimer;
    Eq *eq;
    Pl *playlist;
    Vis *vis;
    HSTREAM channel;
    BOOL played;
    BOOL stopping;
    int duration;
    void setDuration();
    void updateHFX();
    void setHand();
    void loadConf();
    void playNext();
    void setTitle();
    void showEq(bool vis);
    void showPl(bool vis);
    void showVis(bool vis);
    void setStyle(QString file);
    HFX hand80;
    HFX hand170;
    HFX hand300;
    HFX hand600;
    HFX hand1200;
    HFX hand2400;
    HFX hand4800;
    HFX hand9600;
    HFX hand16000;
    QString lastPath;
    QString currplayed;
    QString style;
    QSettings *setting;
    int _tstrl;
    int _cstrct;
    bool _revscr;
    QString _cscr;
private slots:
    void openFile();
    void playPause();
    void stop();
    void Update();
    void setVolume();
    void setPosition();
    void setPan();
    void toggleEQ();
    void togglePL();
    void toggleVis();
    void saveConf();
    void changeTrack(QString str);
};

#endif // MAINWINDOW_H
