#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTimer>
#include <QList>
#include <cstdlib>
#include <time.h>
#include "bass.h"
#include "eq.h"
#include "pl.h"
#include "vis.h"

namespace Ui {
    class MainWindow;
}
void CALLBACK DSP(HDSP handle, DWORD channel, void *buffer, DWORD length, void *user);
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QApplication *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    void contextMenuEvent(QContextMenuEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *titletimer;
    QTimer *checkf;
    QFile *lock;
    uint modtime;
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
    int getPosition();
    DWORD getType();
    QString getTitle();
    void showEq(bool vis);
    void showPl(bool vis);
    void showVis(bool vis);
    void setStyle(QString file);
    void resumePlay();
    void createActions();
    QAction *shuffleAction;
    QAction *repeatAction;
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
    QList<int> *shuffled;
    int current;
    int _lstpos; //last position
    int _tstrl;
    int _cstrct;
    bool _revscr;
    bool shuffle;
    bool isMod;
    bool mute;
    int repeatMode; // 0 - no repeat, 1 - repeat all, 2 - repeal one
    QString _cscr;
private slots:
    void openFile();
    void playPause();
    void stop();
    void Update();
    void setTitle();
    void setVolume();
    void setVolume(int val, bool fade = false);
    void setPosition();
    void setPosition(int pos);
    void setPan();
    void toggleEQ();
    void togglePL();
    void toggleVis();
    void saveConf();
    void changeTrack(QString str);
    void next();
    void prew();
    void turnShuffle();
    void turnShuffle(bool shuffle);
    void setRepeat();
    void setRepeat(int mode);
    void checkFile();
};

#endif // MAINWINDOW_H
