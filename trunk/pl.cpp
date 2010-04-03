#include "pl.h"
#include "ui_pl.h"
#include "bass.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QDir>
#include <QSettings>

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
        }
        else{
            QFile f(file);
            if(f.exists()){
                this->addTrack(file);
            }
        }
    }
}

void Pl::addTrack(QString path)
{
    if(path.isEmpty()){
        return;
    }
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
void Pl::setCurrent(int pos){
    qDebug() << pos;
    this->_curr = pos;
    this->changeTrack(this->tracks->value(pos));
}
int Pl::getCurrent(){
    return this->_curr;
}

bool Pl::save(QString path){
    if(path.isEmpty()){
        qDebug() << "save false...";
        return false;
    }
    if(this->tracks->length() < 1){
        return false;
    }
    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.setTextModeEnabled(true);
    file.write("#EXTM3U\n");
    int l = this->tracks->length();
    for(int i = 0; i < l; i++){
        file.write(QByteArray().append("#EXTINF:0,").append(this->ui->listWidget->item(i)->text().toUtf8()).append("\n"));
        file.write(QByteArray().append(this->tracks->value(i).toUtf8()).append("\n"));
    }
    file.close();
    return true;
}
bool Pl::load(QString path){
    if(path.isEmpty()){
        qDebug() << "load false";
        return false;
    }
    QFile file(path);
    if(!file.exists()){
        qDebug() << "file not found...";
        return false;
    }
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    file.setTextModeEnabled(true);
    if(!file.isOpen()){
        qDebug() << "File is not open...";
    }
    QString str;
    while(file.bytesAvailable() > 0){
        str = QString().fromUtf8(file.readLine(1024)).trimmed();
        if(str.isEmpty() || str.at(0) == '#'){
            continue;
        }
        this->addTrack(str);
    }
    qDebug() << file.errorString();
    file.close();
    return true;
}
