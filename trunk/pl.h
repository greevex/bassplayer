#ifndef PL_H
#define PL_H

#include <QDialog>
#include <QList>
#include <QFileInfo>
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
    QString current();

protected:
    void changeEvent(QEvent *e);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    Ui::Pl *ui;
    QList<QString> *tracks;
    QList<QString> *names;
    int _curr;
private slots:
    void trackClick(QListWidgetItem *qlwi);
signals:
            void changeTrack(QString);
};

#endif // PL_H
