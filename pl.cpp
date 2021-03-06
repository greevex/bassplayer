#include "pl.h"
#include "ui_pl.h"
#include "bass.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QMessageBox>


#define loadproc                    qDebug() << "Loading proc in Pl:" <<


Pl::Pl(QWidget *parent) : QDialog(parent), ui(new Ui::Pl)
{
    this->_curr = 0;
    this->_currs = 0;
    this->path = PATH + "/playlist.m3u";
    loadproc "setup ui";
    ui->setupUi(this);
    loadproc "setup ui properties";
    this->setWindowTitle("Playlist");
    this->setWindowFlags(Qt::Tool | Qt::MSWindowsFixedSizeDialogHint);
    this->ui->listWidget->setAcceptDrops(true);
    this->ui->listWidget->setMaximumWidth(this->width());
    this->ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->listWidget->setSelectionMode(QAbstractItemView::ContiguousSelection);
    loadproc "create actions";
    this->createActions();
    this->ourl = new OpenUrl(this);
    this->ourl->hide();
    connect(this->ourl, SIGNAL(okPressed()), this, SLOT(addUrlf()));
    connect(this->ourl, SIGNAL(canceled()), this, SLOT(urlCanceled()));
    connect(this->ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(trackClick(QListWidgetItem*)));
    connect(this->ui->searchInput, SIGNAL(textChanged(QString)), this, SLOT(search(QString)));
    connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(nextSearch()));
}
Pl::~Pl()
{
    delete ui;
}
void Pl::createActions(){
    this->del = new QAction("Delete", this);
    this->del->setIcon(QIcon(":/res/icons/delete.png"));
    connect(this->del, SIGNAL(triggered()), this, SLOT(deleteItem()));

    this->addu = new QAction("Add URL", this);
    this->addu->setIcon(QIcon(":/res/icons/url.png"));
    connect(this->addu, SIGNAL(triggered()), this, SLOT(addUrl()));
}
void Pl::contextMenuEvent(QContextMenuEvent *event){
    QMenu menu(this);
    menu.addAction(this->del);
    menu.addAction(this->addu);
    menu.exec(event->globalPos());
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
    QList<QUrl> urls = event->mimeData()->urls();
    QString file;
    for(int i = 0; i < urls.length(); i++){
        if(urls.value(i).scheme() == URLCHEME){
            this->addURL(urls.value(i));
        }
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
bool Pl::addTrack(QString path)
{
    if(path.isEmpty() || !QFile(path).exists()){
        return false;
    }
    QFileInfo *f = new QFileInfo(path);
    QListWidgetItem *trk = new QListWidgetItem(this->ui->listWidget);
    trk->setText(f->fileName());
    trk->setData(Qt::UserRole, path.replace('\\', "/", Qt::CaseInsensitive));
    delete f;
    return true;
}
bool Pl::addURL(QUrl url){
    if(url.scheme() != URLCHEME || !url.isValid()){
        return false;
    }
    QListWidgetItem *itm = new QListWidgetItem(this->ui->listWidget);
    itm->setText(url.authority());
    itm->setData(Qt::UserRole, url.toString(QUrl::None));
    return true;
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
   this->_curr =  this->ui->listWidget->row(qlwi);
   this->changeTrack(qlwi->data(Qt::UserRole).toString());
    this->select(this->_curr);
}
QString Pl::current(){
    if(this->_curr >= this->ui->listWidget->count())
        this->_curr = 0;
    this->select(this->_curr);
    return this->ui->listWidget->item(this->_curr)->data(Qt::UserRole).toString();
}
void Pl::setCurrent(int pos){
    if(this->ui->listWidget->count() == 0){
        return;
    }
    if(this->ui->listWidget->count() < 1){
        return;
    }
    if(pos < 0){
        pos = this->ui->listWidget->count() - 1;
    }
    if(pos >= this->ui->listWidget->count()){
        pos = 0;
    }
    this->_curr = pos;
    this->changeTrack(this->ui->listWidget->item(this->_curr)->data(Qt::UserRole).toString());
    this->select(this->_curr);
}
int Pl::getCurrent(){
    return this->_curr;
}
int Pl::getMax(){
    return this->ui->listWidget->count() - 1;
}
void Pl::select(int idx){
    if(this->isVisible()){
        QList<QListWidgetItem *> items = this->ui->listWidget->selectedItems();
        for(int i = 0; i < items.length(); i++){
            items.value(i)->setSelected(false);
        }
        if(!this->ui->listWidget->item(idx)){
            return;
        }
        this->ui->listWidget->item(idx)->setSelected(true);
        this->ui->listWidget->scrollToItem(this->ui->listWidget->item(idx), QAbstractItemView::EnsureVisible);
    }
}
bool Pl::save(){
    if(path.isEmpty()){
        return false;
    }
    if(this->ui->listWidget->count() < 1){
        return false;
    }
    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.setTextModeEnabled(true);
    file.write("#EXTM3U\n");
    int l = this->ui->listWidget->count();
    for(int i = 0; i < l; i++){
        file.write(QByteArray().append("#EXTINF:0,").append(this->ui->listWidget->item(i)->text().toUtf8()).append("\n"));
        file.write(QByteArray().append(this->ui->listWidget->item(i)->data(Qt::UserRole).toString().toUtf8()).append("\n"));
    }
    file.close();
    return true;
}
bool Pl::load(QString path){
    if(path.isEmpty()){
        return false;
    }
    QFile file(path);
    if(!file.exists()){
        return false;
    }
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    file.setTextModeEnabled(true);
    if(!file.isOpen()){
    }
    QString str;
    QString title;
    while(file.bytesAvailable() > 0){
        str = QString().fromUtf8(file.readLine(1024)).trimmed();
        if(str.isEmpty()){
            continue;
        }
        else{
            if(str.at(0) == '#' && title.isEmpty()){
                if(str.left(10) == "#EXTINF:0,"){
                    title = str.mid(10);
                }
                else{
                    title = "";
                }
            }
        }
        if(this->addTrack(str)){
            if(!title.isEmpty()){
                this->setTitle(this->ui->listWidget->count() - 1, title);
                title = "";
            }
        }
        else if(this->addURL(str)){
            if(!title.isEmpty()){
                this->setTitle(this->ui->listWidget->count() - 1, title);
                title = "";
            }
        }
    }
    file.close();
    return true;
}
void Pl::setTitle(int idx, QString title){
    if(idx >= 0 && idx < this->ui->listWidget->count()){
        this->ui->listWidget->item(idx)->setText(title);
    }
}
void Pl::deleteItem(){
    bool change = false;
    QList<QListWidgetItem *> items = this->ui->listWidget->selectedItems();
    if(items.length() > 0){
        for(int i = 0; i < items.length(); i++){
            int pos = this->ui->listWidget->row(items.value(i));
            this->ui->listWidget->removeItemWidget(items.value(i));
            if(pos < this->_curr){
                this->_curr--;
            }
            else if(pos == this->_curr){
                change = true;
                this->_curr++;
            }
            delete items.value(i);
        }
    }
    if(change){
        this->setCurrent(this->_curr);
    }
}
void Pl::hideEvent(QHideEvent *event){
}
void Pl::showEvent(QShowEvent *event){
    this->select(this->_curr);
}
void Pl::search(QString s){
    QBrush brush(NORMALCOLOR, Qt::SolidPattern);
    this->ui->listWidget->item(this->_currs)->setBackground(brush);
    this->_currs = 0;
    if(s.isEmpty() || s.length() < 2){
        return;
    }
    this->searcha(s);
}
void Pl::searcha(QString s){
    QBrush brush(SELECTEDCOLOR, Qt::Dense1Pattern);
    this->lastSearch = s;
    int len = this->ui->listWidget->count();
    bool repeated = false;
    if(this->_currs > len){
        this->_currs = 0;
    }
    for(int i = this->_currs; i < len; i++){
        if(this->ui->listWidget->item(i)->text().contains(s, Qt::CaseInsensitive)){
            this->_currs = i;
            this->ui->listWidget->item(i)->setBackground(brush);
            this->ui->listWidget->scrollToItem(this->ui->listWidget->item(i), QAbstractItemView::EnsureVisible);
            return;
        }
        if(i == len - 1 && !repeated){
            i = 0;
            repeated = true;
        }
    }
}
void Pl::nextSearch(){
    this->ui->listWidget->item(this->_currs)->setBackground(QBrush(NORMALCOLOR, Qt::SolidPattern));
    this->_currs++;
    this->searcha(this->lastSearch);
}
void Pl::clear(){
    int len = this->ui->listWidget->count();
    for(int i = len - 1; i > -1; i--){
        delete this->ui->listWidget->item(i);
    }
    this->_curr = 0;
    this->_currs = 0;
}
void Pl::addUrl(){
    this->ourl->show();
}
void Pl::addUrlf(){
    QUrl url(this->ourl->getURL());
    if(url.scheme() == URLCHEME && url.isValid()){
        this->addURL(url);
    }
    this->ourl->hide();
}
void Pl::urlCanceled(){
    this->ourl->hide();
}
