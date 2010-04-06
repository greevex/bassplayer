#ifndef PL_H
#define PL_H

#include <QDialog>
#include <QList>
#include <QFileInfo>
#include <QTimer>
#include <QContextMenuEvent>
#include <QAction>
#include <QMenu>
#include <QMoveEvent>
#include "ui_pl.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

namespace Ui {
    class Pl;
}

class Pl : public QDialog {
    Q_OBJECT
public:
    Pl(QWidget *parent = 0);
    ~Pl();
    bool addTrack(QString path);
    void addPath(QString path);
    void next(QString file);
    bool load(QString path);
    bool save();
    QString current();
    QString path;
    void setCurrent(int pos);
    int getCurrent();
    int getMax();
    void setTitle(int idx, QString title);

protected:
    void changeEvent(QEvent *e);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void hideEvent(QHideEvent *event);

private:
    Ui::Pl *ui;
    QList<QString> *tracks;
    void select(int idx);
    void createActions();
    QTimer *tmr;
    QAction *del;
    const char* html;
    int _curr;
private slots:
    void trackClick(QListWidgetItem *qlwi);
    void deleteItem();
signals:
    void changeTrack(QString);
};

#endif // PL_H
