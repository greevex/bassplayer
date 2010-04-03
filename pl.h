#ifndef PL_H
#define PL_H

#include <QDialog>
#include <QList>
#include <QFileInfo>
#include <QTimer>
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
    void addTrack(QString path);
    void addPath(QString path);
    void next(QString file);
    bool load(QString path);
    QString current();
    QString path;
    void setCurrent(int pos);
    int getCurrent();

protected:
    void changeEvent(QEvent *e);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    Ui::Pl *ui;
    QList<QString> *tracks;
    QList<QString> *names;
    void select(int idx);
    int _curr;
    QTimer *tmr;
private slots:
    void trackClick(QListWidgetItem *qlwi);
    bool save();
signals:
            void changeTrack(QString);
};

#endif // PL_H
