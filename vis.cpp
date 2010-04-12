#include "vis.h"
#include "ui_vis.h"
#include <QPainter>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>

#define FPS 40
#define loadproc qDebug() << "Loading process in Vis:" <<



Vis::Vis(QWidget *parent) : QDialog(parent), ui(new Ui::Vis)
{
    this->ctype = 1;
    this->curr = -1;
    this->setWindowFlags(Qt::Tool);
    this->timer = new QTimer(this);
    this->timer->setInterval((int)(1000 / FPS));
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->libs = new QStringList();
    this->libsinfo = new QList<VisInfo*>();
    this->actions = new QList<QAction*>();
    ui->setupUi(this);
    this->checkLibs();
    this->createActions();
    this->load();
    this->setTitle();
    if(this->isVisible())
        this->timer->start();
}
Vis::~Vis()
{
    delete ui;
}
void Vis::setChannel(HSTREAM chan){
    this->chan = chan;
}
void Vis::changeEvent(QEvent *e)
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
void Vis::paintEvent(QPaintEvent *event){
    if(!this->isVisible()){
        return;
    }
    BASS_ChannelGetData(this->chan, fft, BASS_DATA_FFT8192); //получение даных БФП
    if(this->ctype == 1){
        if(this->Draw){
            QPainter paint(this);
            this->Draw(paint, fft);
        }
        else{
            qDebug() << "error: cold not resolve Draw...";
        }
    }
    else if(this->ctype == 2){
        if(this->Upd){
            this->Upd(fft);
        }
        else{
            err << "could't resolve Update()";
        }
    }
    memset(fft, 0, 16384);
}
void Vis::checkLibs(){
    loadproc "loading visualization plugins";
    QDir dir("./plugins");
    if(dir.exists()){
        QStringList filters;
        filters.append("vis_*.dll");
        filters.append("vis_*.so");
        filters.append("libvis_*.so");
        filters.append("libvis_*.so*");
        QStringList list = dir.entryList(filters, QDir::Files);
        for(int i = 0; i < list.length(); i++){
            if(QLibrary::isLibrary("./plugins/" + list.value(i))){
                VisInf inf = (VisInf)QLibrary::resolve("./plugins/" + list.value(i), "Info");
                if(!inf){
                    continue;
                }
                else{
                    VisInfo * vinf = new VisInfo();
                    inf(vinf);
                    this->libs->append(list.value(i));
                    this->libsinfo->append(vinf);
                    loadproc "plugin" << list.value(i) << "added";
                }
            }
        }
    }
}
void Vis::createActions(){
    for(int i = 0; i < this->libs->length(); i++){
        QAction *action = new QAction(this->libsinfo->value(i)->name, this);
        action->setData(i);
        action->setIcon(QIcon(":/res/icons/plugin.png"));
        connect(action, SIGNAL(triggered()), this, SLOT(changeVis()));
        this->actions->append(action);
    }
    QAction *about = new QAction("About", this);
    about->setIcon(QIcon(":/res/icons/information.png"));
    connect(about, SIGNAL(triggered()), this, SLOT(about()));
    this->actions->append(about);
    QAction *fs = new QAction("Toggle Fullscreen", this);
    fs->setIcon(QIcon(":/res/icons/fullscreen.png"));
    connect(fs, SIGNAL(triggered()), this, SLOT(toggleFullScreen()));
    this->actions->append(fs);
}
void Vis::contextMenuEvent(QContextMenuEvent *event){
    QMenu menu(this);
    for(int i = 0; i < this->actions->length(); i++){
        menu.addAction(this->actions->value(i));
    }
    menu.exec(event->globalPos());
}
void Vis::changeVis(){
    QAction *act = qobject_cast<QAction*>(sender());
    int libid = act->data().toInt();
    this->unload();
    this->load(this->libs->value(libid));
    this->setTitle();
    this->curr = libid;
}
void Vis::hideEvent(QHideEvent *event){
    this->timer->stop();
    if(this->curr != -1)
        this->unload();
}
void Vis::showEvent(QShowEvent *event){
    if(this->curr != -1)
        this->load(this->libs->value(this->curr));
    this->timer->start();
}
void Vis::about(){
    if(this->vislib->isLoaded()){
        VisInf inf = (VisInf)this->vislib->resolve("Info");
        if(inf){
            VisInfo *vinf = new VisInfo();
            inf(vinf);
            QMessageBox::about(this, "About " + vinf->name,
                               "<h2>" + vinf->name + "</h2><br />" +
                               "<div style='text-align: left;'>" +
                                "<b>Autor:</b> " + vinf->autor + "<br />" +
                                "<b>Version:</b> " + vinf->version +
                               "</div>"
                               );
        }
    }
}
void Vis::toggleFullScreen(){
    if(!this->isFullScreen()){
        this->setWindowState(Qt::WindowFullScreen);
    }
    else{
        this->setWindowState(Qt::WindowNoState);
    }
}
void Vis::save(){
    QSettings s("./vis.ini", QSettings::IniFormat);
    s.setValue("dll", this->curr == -1 ? "" : this->libs->value(this->curr));
    s.setValue("W", this->width());
    s.setValue("H", this->height());
}
void Vis::load(QString dll){
    this->vislib = new QLibrary("./plugins/" + dll);
    VisInf inf = (VisInf)this->vislib->resolve("Info");
    if(inf){
        VisInfo *vinf = new VisInfo();
        inf(vinf);
        if(vinf->ver == 2){
            this->ctype = 2;
            INIT init = (INIT)this->vislib->resolve("Init");
            if(init){
                init(this->window());
                this->Upd = (UPDATE)this->vislib->resolve("Update");
            }
            else{
                err << "could't resolve Init()";
            }
        }
        else{
            this->ctype = 1;
            this->Draw = (Drawer)this->vislib->resolve("Draw");
        }
    }
    this->curr = this->libs->indexOf(dll, 0);
}
void Vis::load(){
    QSettings s("./vis.ini", QSettings::IniFormat);
    this->resize(s.value("W", this->minimumWidth()).toInt(), s.value("H", this->minimumHeight()).toInt());
    this->load(s.value("dll", "vis_spect.dll").toString());
}
void Vis::unload(){
    if(this->ctype == 2){
        this->Upd = NULL;
        STOP stop = (STOP)this->vislib->resolve("Stop");
        if(stop){
            stop();
        }
    }
    else{
        this->Draw = NULL;
    }
    this->vislib->unload();
    delete this->vislib;
}
void Vis::setTitle(){
   VisInf inf = (VisInf)this->vislib->resolve("Info");
   if(inf){
       VisInfo *info = new VisInfo();
       inf(info);
       this->setWindowTitle(info->name);
       delete info;
       return;
   }
   else{
       qDebug() << "error: could't resolve Info()";
   }
   this->setWindowTitle("Visualization");
}
