#include "vis.h"
#include "ui_vis.h"
#include <QPainter>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>

#define FPS 40

typedef void (*Drawer)(QPainter&, float*);
typedef void (*VisInf)(VisInfo*);

Vis::Vis(QWidget *parent) : QDialog(parent), ui(new Ui::Vis)
{
    this->fps = FPS;
    this->setWindowFlags(Qt::Tool);
    this->timer = new QTimer(this);
    this->timer->setInterval((int)(1000 / fps));
    connect(this->timer, SIGNAL(timeout()), this, SLOT(repaint()));
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
    if(this->isVisible()){
        if(this->fps != FPS){
            this->fps = FPS;
            this->timer->setInterval((int)(1000 /this->fps));
        }
        Drawer Draw = (Drawer)vislib->resolve("Draw");
        QPainter paint(this);
        if(Draw){
            BASS_ChannelGetData(this->chan, fft, BASS_DATA_FFT8192); //получение даных БФП
            Draw(paint, fft);
            memset(fft, 0, 16384);
        }
        else{
            qDebug() << "error: cold not resolve Draw...";
        }
    }
    else{
        this->fps = 1;
        this->timer->setInterval((int)(1000 / this->fps));
    }
}
void Vis::checkLibs(){
    QDir dir("./plugins");
    if(dir.exists()){
        QStringList filters;
        filters.append("vis_*.dll");
        filters.append("vis_*.so");
        QStringList list = dir.entryList(filters, QDir::Files);
        for(int i = 0; i < list.length(); i++){
            qDebug() << "checking: " << list.value(i);
            if(QLibrary::isLibrary("./plugins/" + list.value(i))){
                VisInf inf = (VisInf)QLibrary::resolve("./plugins/" + list.value(i), "Info");
                if(!inf){
                    qDebug() << "error: could't resolve method Info";
                    continue;
                }
                else{
                    VisInfo * vinf = new VisInfo();
                    inf(vinf);
                    this->libs->append(list.value(i));
                    this->libsinfo->append(vinf);
                    qDebug() << "added: " << list.value(i) << ", autor: " << vinf->autor << ", name: " << vinf->name << ", version: " << vinf->version;
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
    if(!this->vislib->unload()){
        qDebug() << "error unloading library...";
    }
    delete this->vislib;
    this->vislib = new QLibrary(this->libs->value(libid));
    qDebug() << "vis lib chaged to" << this->libsinfo->value(libid)->name;
    this->setTitle();
}
void Vis::hideEvent(QHideEvent *event){
    this->timer->stop();
}
void Vis::showEvent(QShowEvent *event){
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
    s.setValue("dll", this->vislib->fileName());
    s.setValue("W", this->width());
    s.setValue("H", this->height());
}
void Vis::load(){
    QSettings s("./vis.ini", QSettings::IniFormat);
    this->vislib = new QLibrary(s.value("dll", "./plugins/vis_spect.dll").toString());
    this->resize(s.value("W", this->minimumWidth()).toInt(), s.value("H", this->minimumHeight()).toInt());
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
