#ifndef PL_H
#define PL_H

#include <QDialog>
#include <QList>
#include <QFileInfo>
#include <QContextMenuEvent>
#include <QAction>
#include <QMenu>
#include "ui_pl.h"
#include "openurl.h"

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
    void addURL(QUrl url);
    bool load(QString path);
    bool save();
    QString current();
    QString path;
    void setCurrent(int pos);
    int getCurrent();
    int getMax();
    void setTitle(int idx, QString title);
    void clear();

protected:
    void changeEvent(QEvent *e);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);

private:
    Ui::Pl *ui;
    void select(int idx);
    void createActions();
    QAction *del;
    QAction *addu;
    const char* html;
    int _curr;
    int _currs;
    void searcha(QString s);
    QString lastSearch;
    OpenUrl *ourl;
private slots:
    void trackClick(QListWidgetItem *qlwi);
    void deleteItem();
    void addUrl();
    void addUrlf();
    void urlCanceled();
    void search(QString s);
    void nextSearch();
signals:
    void changeTrack(QString);
};

#endif // PL_H
