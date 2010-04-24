#ifndef OPENURL_H
#define OPENURL_H

#include <QDialog>

namespace Ui {
    class OpenUrl;
}

class OpenUrl : public QDialog {
    Q_OBJECT
public:
    OpenUrl(QWidget *parent = 0);
    QString getURL();
    ~OpenUrl();
signals:
    void okPressed();
    void canceled();
protected:
    void changeEvent(QEvent *e);
private slots:
    void ok();
    void cancel();
private:
    Ui::OpenUrl *ui;
};

#endif // OPENURL_H
