#include "vis.h"
#include "ui_vis.h"
#include <QPainter>
#include <QDir>
#include <QDebug>

#define FPS 50
Vis::Vis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vis)
{
    this->fps = FPS;
    this->setWindowTitle("Spectr");
    this->setWindowFlags(Qt::Tool | Qt::MSWindowsFixedSizeDialogHint);
    this->timer = new QTimer(this);
    this->timer->setInterval((int)(1000 / fps));
    connect(this->timer, SIGNAL(timeout()), this, SLOT(repaint()));
    this->timer->start();
    this->libs = new QStringList();
    this->libsinfo = new QList<VisInfo*>();
    this->actions = new QList<QAction*>();
    this->checkLibs();
    this->createActions();
    this->vislib = new QLibrary("vis_spect");
    ui->setupUi(this);
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
        typedef void (*Drawer)(QPainter&, float*);
        Drawer Draw = (Drawer)vislib->resolve("Draw");
        QPainter paint(this);
        BASS_ChannelGetData(this->chan, fft, BASS_DATA_FFT4096); //получение даных БФП
        Draw(paint, fft);

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
                qDebug() << "create typedef...";
                typedef void (*VisInf)(VisInfo*);
                VisInf inf = (VisInf)QLibrary::resolve("./plugins/" + list.value(i), "Info");
                qDebug() << "typedef create success...";
                if(!inf){
                    qDebug() << "could't resolve method Info";
                    continue;
                }
                else{
                    qDebug() << "create struct obj...";
                    VisInfo * vinf = new VisInfo();
                    qDebug() << "launch Info()...";
                    inf(vinf);
                    qDebug() << "appending";
                    this->libs->append(list.value(i));
                    this->libsinfo->append(vinf);
                    qDebug() << "added: " << list.value(i) << ", autor: " << vinf->autor << ", name: " << vinf->name << ", version: " << vinf->version;
                }
            }
            qDebug() << "end checking:" << list.value(i);
        }
    }
}
void Vis::createActions(){
    for(int i = 0; i < this->libs->length(); i++){
        QAction *action = new QAction(this->libsinfo->value(i)->name, this);
        action->setData(i);
        connect(action, SIGNAL(triggered()), this, SLOT(changeVis()));
        this->actions->append(action);
    }
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
    this->vislib->unload();
    this->vislib->~QLibrary();

    this->vislib = new QLibrary(this->libs->value(libid));

    qDebug() << "vis lib chaged to" << this->libsinfo->value(libid)->name;
}
