#include "pl.h"
#include "ui_pl.h"
#include "bass.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QDir>

Pl::Pl(QWidget *parent) : QDialog(parent),
    ui(new Ui::Pl)
{
    this->setWindowTitle("Playlist");
    this->setWindowFlags(Qt::Tool | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    this->tracks = new QList<QString>();
    this->names = new QList<QString>();
    this->ui->listWidget->setAcceptDrops(true);
    connect(this->ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(trackClick(QListWidgetItem*)));
    this->_curr = 0;
}

Pl::~Pl()
{
    delete ui;
}

void Pl::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void Pl::dragEnterEvent(QDragEnterEvent *event){
    if(event->mimeData()->hasUrls()){
        event->setDropAction(Qt::ActionMask);
        event->accept();
    }
}
void Pl::dropEvent(QDropEvent *event){
    qDebug() << "dropped...";
    qDebug() << event->mimeData()->urls().value(0).toString(QUrl::None);
    QList<QUrl> urls = event->mimeData()->urls();
    QString file;
    for(int i = 0; i < urls.length(); i++){
        file = urls.value(i).toString(QUrl::None);
#ifdef Q_WS_WIN //windows, cut file:///
        file = file.mid(8);
#else
        file = file.mid(7); //other, cut file://
#endif
        QDir dir(file);
        if(dir.exists()){
            this->addPath(file);
            dir.~QDir();
        }
        else{
            QFile f(file);
            if(f.exists()){
                this->addTrack(file);
                f.~QFile();
            }
        }
    }
}

void Pl::addTrack(QString path)
{
        qDebug() << "added: " + path;
        this->tracks->append(path);
        QFileInfo *f = new QFileInfo(path);
        this->names->append(f->fileName());
        QListWidgetItem *trk = new QListWidgetItem(this->ui->listWidget);
        trk->setText(this->names->last());
}
void Pl::addPath(QString path){
    QDir dir(path);
    if(dir.exists()){
        QStringList listd = dir.entryList(QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDir::Name);
        for(int i = 0; i < listd.length(); i++){
            this->addPath(dir.path() + "/" + listd.value(i));
        }
        QStringList listf = dir.entryList(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDir::Name);
        for(int i = 0; i < listf.length(); i++){
            this->addTrack(dir.path() + "/" + listf.value(i));
        }
    }
}

void Pl::trackClick(QListWidgetItem *qlwi)
{
   int row =  this->ui->listWidget->row(qlwi);
   this->changeTrack(this->tracks->value(row));
    qDebug() << "click" << qlwi->text() << this->tracks->value(row);
    this->_curr = row;
    this->ui->listWidget->setItemSelected(this->ui->listWidget->item(row), true);
}
void Pl::next(QString file)
{
    int pos = this->tracks->indexOf(file, 0)+1;
    int len = this->tracks->length();
    qDebug() <<  pos << " " << len;
    if(pos == len)
        pos = 0;
    this->changeTrack(this->tracks->value(pos));
    this->ui->listWidget->setItemSelected(this->ui->listWidget->item(pos), true);
    this->_curr++;
}
QString Pl::current(){
    if(this->_curr >= this->tracks->length())
        this->_curr = 0;
    this->ui->listWidget->setItemSelected(this->ui->listWidget->item(this->_curr), true);
    return this->tracks->value(this->_curr);
}