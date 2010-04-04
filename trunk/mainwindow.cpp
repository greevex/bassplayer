#include <QtGui>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication *parent) : QMainWindow(), ui(new Ui::MainWindow)
{
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    BASS_Init(-1, 44100, 0, NULL, NULL);
    this->_tstrl = 20;
    this->_cstrct = 0;
    this->duration = 0;
    this->_cscr = "";
    this->currplayed = "";
    this->lastPath = "./";
    this->_revscr = false;
    this->played = false;
    this->conftimer = new QTimer(this);
    this->timer = new QTimer(this);
    this->titletimer = new QTimer(this);
    this->eq = new Eq(this);
    this->playlist = new Pl(this);
    this->vis = new Vis(this);
    this->setHand();
    this->loadConf();
    this->timer->setInterval(100);
    this->conftimer->setInterval(1000);
    this->titletimer->setInterval(500);
    this->conftimer->start();
    this->titletimer->start();
    this->stopping = true;
    this->setStyle(this->style);
    this->playlist->load(this->playlist->path);
    this->createActions();
    this->resumePlay();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::contextMenuEvent(QContextMenuEvent *event){
    QMenu menu(this);
    menu.addAction(this->shuffleAction);
    menu.addAction(this->repeatAction);
    menu.exec(event->globalPos());
}
void MainWindow::createActions(){
    this->shuffleAction = new QAction("Shuffle", this);
    this->shuffleAction->setShortcuts(QKeySequence::Replace);
    connect(this->shuffleAction, SIGNAL(triggered()), this, SLOT(turnShuffle()));

    this->repeatAction = new QAction("Repeat", this);
    this->repeatAction->setShortcuts(QKeySequence::New);
    connect(this->repeatAction, SIGNAL(triggered()), this, SLOT(setRepeat()));
}

void MainWindow::setHand()
{
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(playPause()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(stop()));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(setPosition()));
    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(setVolume()));
    connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this, SLOT(setPan()));
    connect(this->timer, SIGNAL(timeout()), this, SLOT(Update()));
    connect(this->conftimer, SIGNAL(timeout()), this, SLOT(saveConf()));
    connect(this->titletimer, SIGNAL(timeout()), this, SLOT(setTitle()));
    connect(this->ui->pushButton_4, SIGNAL(clicked()), this, SLOT(toggleEQ()));
    connect(this->ui->pushButton_5, SIGNAL(clicked()), this, SLOT(togglePL()));
    connect(this->ui->pushButton_6, SIGNAL(clicked()), this, SLOT(toggleVis()));
    connect(this->ui->pushButton_7, SIGNAL(clicked()), this, SLOT(next()));
    connect(this->ui->pushButton_8, SIGNAL(clicked()), this, SLOT(prew()));
    connect(this->playlist, SIGNAL(changeTrack(QString)), this, SLOT(changeTrack(QString)));
}
void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void MainWindow::openFile()
{
    QStringList file = QFileDialog::getOpenFileNames(this, "", this->lastPath);
    this->lastPath = file.value(0);
    for(int i = 0; i < file.length(); i++)
        this->playlist->addTrack(file.value(i));
    if(!this->played)
    {
        BASS_StreamFree(this->channel);
        this->channel = BASS_StreamCreateFile(false, file.value(0).toLocal8Bit().constData(), 0, 0, 0);
        this->stopping = false;
        this->setVolume();
        this->setDuration();
        this->timer->start();
        this->updateHFX();
        this->eq->setEq();
        this->playPause();
        this->currplayed = file.value(0);
    }
}
void MainWindow::playPause()
{
    if(BASS_ChannelIsActive(this->channel) == BASS_ACTIVE_PLAYING)
        BASS_ChannelPause(this->channel);
    else
    {
        if(this->stopping){
            this->stopping = false;
            this->changeTrack(this->playlist->current());
            return;
        }
        this->stopping = false;
        if(this->played == true)
            BASS_ChannelPlay(this->channel, false);
        else
            BASS_ChannelPlay(this->channel, true);
    }
    this->played = true;
}
void MainWindow::stop()
{
    BASS_ChannelStop(this->channel);
    this->played = false;
    this->stopping = true;
    this->timer->stop();
}
void MainWindow::Update()
{
    if(BASS_ChannelIsActive(this->channel) == BASS_ACTIVE_STOPPED && !this->stopping)
    {
        this->next();
    }
    int currPos = this->getPosition();
    this->ui->horizontalSlider->setValue(currPos);
    //current position
    QString min = QString().setNum((currPos / 60));
    QString sec = QString().setNum((currPos % 60));
    if(min.size() == 1)
        min.prepend("0");
    if(sec.size() == 1)
        sec.prepend("0");
    //duration
    QString dmin = QString().setNum(this->duration / 60);
    QString dsec = QString().setNum(this->duration % 60);
    if(dmin.size() == 1)
        dmin.prepend("0");
    if(dsec.size() == 1)
        dsec.prepend("0");
    //
    QString time = QString().append(min).append(":").append(sec).append("/").append(dmin).append(":").append(dsec);
    this->ui->label->setText(time);
    this->vis->setChannel(this->channel);
}
void MainWindow::setDuration()
{
    QWORD l = BASS_ChannelGetLength(this->channel, BASS_POS_BYTE);
    this->duration = (int)BASS_ChannelBytes2Seconds(this->channel, l);
    this->ui->horizontalSlider->setMaximum(this->duration);
}
void MainWindow::setPosition()
{
    QWORD pos = BASS_ChannelSeconds2Bytes(this->channel, (double)ui->horizontalSlider->value());
    BASS_ChannelSetPosition(this->channel, pos, BASS_POS_BYTE);
}
void MainWindow::setPosition(int pos){
    QWORD pos1 = BASS_ChannelSeconds2Bytes(this->channel, (double)pos);
    BASS_ChannelSetPosition(this->channel, pos1, BASS_POS_BYTE);
}
int MainWindow::getPosition(){
    QWORD pos = BASS_ChannelGetPosition(this->channel, BASS_POS_BYTE);
    return (int)BASS_ChannelBytes2Seconds(this->channel, pos);
}
void MainWindow::setVolume()
{
    float f = (float)ui->horizontalSlider_2->value()/100;
    BASS_ChannelSetAttribute(this->channel, BASS_ATTRIB_VOL, f);
}
void MainWindow::setPan()
{
    float pan = (float)(this->ui->horizontalSlider_3->value() - 10) / 10;
    BASS_ChannelSetAttribute(this->channel, BASS_ATTRIB_PAN, pan);
}
void MainWindow::updateHFX()
{
    this->eq->e80 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e120 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e150 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e200 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e250 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e300 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e400 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e500 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e600 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e700 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e800 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e900 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e1000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e2000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e3000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e4000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e5000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e6000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e7000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e8000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e9000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e10000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e11000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e12000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e13000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e14000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e15000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
    this->eq->e16000 = BASS_ChannelSetFX(this->channel, BASS_FX_DX8_PARAMEQ, 1);
}
void MainWindow::saveConf()
{
    QSettings setting("./setting.ini", QSettings::IniFormat, this);
    setting.setValue("Conf", 1);
    setting.setValue("Volume", ui->horizontalSlider_2->value());
    setting.setValue("Pan", this->ui->horizontalSlider_3->value());
    setting.setValue("X", this->x());
    setting.setValue("Y", this->y());
    setting.setValue("LastPath", this->lastPath);
    setting.setValue("Eq1", this->eq->getEq(80));
    setting.setValue("Eq2", this->eq->getEq(120));
    setting.setValue("Eq3", this->eq->getEq(150));
    setting.setValue("Eq4", this->eq->getEq(200));
    setting.setValue("Eq5", this->eq->getEq(250));
    setting.setValue("Eq6", this->eq->getEq(300));
    setting.setValue("Eq7", this->eq->getEq(400));
    setting.setValue("Eq8", this->eq->getEq(500));
    setting.setValue("Eq9", this->eq->getEq(600));
    setting.setValue("Eq10", this->eq->getEq(700));
    setting.setValue("Eq11", this->eq->getEq(800));
    setting.setValue("Eq12", this->eq->getEq(900));
    setting.setValue("Eq13", this->eq->getEq(1000));
    setting.setValue("Eq14", this->eq->getEq(2000));
    setting.setValue("Eq15", this->eq->getEq(3000));
    setting.setValue("Eq16", this->eq->getEq(4000));
    setting.setValue("Eq17", this->eq->getEq(5000));
    setting.setValue("Eq18", this->eq->getEq(6000));
    setting.setValue("Eq19", this->eq->getEq(7000));
    setting.setValue("Eq20", this->eq->getEq(8000));
    setting.setValue("Eq21", this->eq->getEq(9000));
    setting.setValue("Eq22", this->eq->getEq(10000));
    setting.setValue("Eq23", this->eq->getEq(11000));
    setting.setValue("Eq24", this->eq->getEq(12000));
    setting.setValue("Eq25", this->eq->getEq(13000));
    setting.setValue("Eq26", this->eq->getEq(14000));
    setting.setValue("Eq27", this->eq->getEq(15000));
    setting.setValue("Eq28", this->eq->getEq(16000));
    setting.setValue("ShowEQ", this->eq->isVisible());
    setting.setValue("ShowPL", this->playlist->isVisible());
    setting.setValue("ShowVis", this->vis->isVisible());
    setting.setValue("EqPosX", this->eq->x());
    setting.setValue("EqPosY", this->eq->y());
    setting.setValue("PlPosX", this->playlist->x());
    setting.setValue("PlPosY", this->playlist->y());
    setting.setValue("VisPosX", this->vis->x());
    setting.setValue("VisPosY", this->vis->y());
    setting.setValue("Style", this->style);
    setting.setValue("PlayList", "./playlist.m3u");
    setting.setValue("LastPlayed", this->playlist->getCurrent());
    setting.setValue("LastPosition", this->getPosition());
}
void MainWindow::loadConf()
{

    QSettings setting("./setting.ini", QSettings::IniFormat, this);
    if(setting.value("Conf", QVariant::Int).toInt() == 1)
    {
        this->move(setting.value("X", 0).toInt(), setting.value("Y", 0).toInt());
        this->ui->horizontalSlider_2->setValue(setting.value("Volume", 20).toInt());
        this->ui->horizontalSlider_3->setValue(setting.value("Pan", 10).toInt());
        this->lastPath = setting.value("LastPath", "./").toString();
        this->eq->setEq(80, setting.value("Eq1", 150).toInt());
        this->eq->setEq(120, setting.value("Eq2", 150).toInt());
        this->eq->setEq(150, setting.value("Eq3", 150).toInt());
        this->eq->setEq(200, setting.value("Eq4", 150).toInt());
        this->eq->setEq(250, setting.value("Eq5", 150).toInt());
        this->eq->setEq(300, setting.value("Eq6", 150).toInt());
        this->eq->setEq(400, setting.value("Eq7", 150).toInt());
        this->eq->setEq(500, setting.value("Eq8", 150).toInt());
        this->eq->setEq(600, setting.value("Eq9", 150).toInt());
        this->eq->setEq(700, setting.value("Eq10", 150).toInt());
        this->eq->setEq(800, setting.value("Eq11", 150).toInt());
        this->eq->setEq(900, setting.value("Eq12", 150).toInt());
        this->eq->setEq(1000, setting.value("Eq13", 150).toInt());
        this->eq->setEq(2000, setting.value("Eq14", 150).toInt());
        this->eq->setEq(3000, setting.value("Eq15", 150).toInt());
        this->eq->setEq(4000, setting.value("Eq16", 150).toInt());
        this->eq->setEq(5000, setting.value("Eq17", 150).toInt());
        this->eq->setEq(6000, setting.value("Eq18", 150).toInt());
        this->eq->setEq(7000, setting.value("Eq19", 150).toInt());
        this->eq->setEq(8000, setting.value("Eq20", 150).toInt());
        this->eq->setEq(9000, setting.value("Eq21", 150).toInt());
        this->eq->setEq(10000, setting.value("Eq22", 150).toInt());
        this->eq->setEq(11000, setting.value("Eq23", 150).toInt());
        this->eq->setEq(12000, setting.value("Eq24", 150).toInt());
        this->eq->setEq(13000, setting.value("Eq25", 150).toInt());
        this->eq->setEq(14000, setting.value("Eq26", 150).toInt());
        this->eq->setEq(15000, setting.value("Eq27", 150).toInt());
        this->eq->setEq(16000, setting.value("Eq28", 150).toInt());
        this->showEq(setting.value("ShowEQ", false).toBool());
        this->showPl(setting.value("ShowPL", false).toBool());
        this->showVis(setting.value("ShowVis", false).toBool());
        this->eq->move(setting.value("EqPosX", 0).toInt(), setting.value("EqPosY", 0).toInt());
        this->playlist->move(setting.value("PlPosX", 0).toInt(), setting.value("PlPosY", 0).toInt());
        this->vis->move(setting.value("VisPosX", 0).toInt(), setting.value("VisPosY", 0).toInt());
        this->vis->setColor(
                 QColor(
                        setting.value("BR", 0).toInt(),
                        setting.value("BG", 0).toInt(),
                        setting.value("BB", 0).toInt()
                        ),
                 QColor(
                        setting.value("PR", 0xff).toInt(),
                        setting.value("PG", 0).toInt(),
                        setting.value("PB", 0).toInt()
                        ),
                 QColor(
                        setting.value("MR", 0).toInt(),
                        setting.value("MG", 0xff).toInt(),
                        setting.value("MB", 0).toInt()
                        )
                );
        this->style = setting.value("Style", "./style.css").toString();
        this->playlist->path = setting.value("Playlist", "./playlist.m3u").toString();
        this->current = setting.value("LastPlayed", 0).toInt();
        this->_lstpos = setting.value("LastPosition", 0).toInt();
    }
}
void MainWindow::resumePlay(){
    this->playlist->setCurrent(this->current);
    this->setPosition(this->_lstpos);
}
void MainWindow::next(){
    this->playlist->setCurrent(this->current + 1);
    this->current = this->playlist->getCurrent();
}
void MainWindow::prew(){
    this->playlist->setCurrent(this->current - 1);
    this->current = this->playlist->getCurrent();
}

void MainWindow::changeTrack(QString str)
{
    this->currplayed = str;
    BASS_StreamFree(this->channel);
    if(!(this->channel = BASS_StreamCreateFile(false, str.toLocal8Bit().constData(), 0, 0, 0)))
        return;
    this->setVolume();
    this->setDuration();
    this->timer->start();
    this->updateHFX();
    this->eq->setEq();
    this->stopping = false;
    this->current = this->playlist->getCurrent();
    this->playPause();
}
void MainWindow::setTitle(){
    if(this->_cscr != this->currplayed){
        this->_cscr = this->currplayed;
        this->_revscr = false;
        this->_cstrct = 0;
    }
    if(_cscr.indexOf('/') == -1){
        return;
    }
    QString name = this->_cscr.split('/', QString::SkipEmptyParts).last();
    int len = name.length();
    if(len > this->_tstrl){
        if(!this->_revscr){
            this->setWindowTitle(name.mid(this->_cstrct, this->_tstrl));
            this->_cstrct++;
            if(len <= this->_cstrct + this->_tstrl)
                this->_revscr = true;
        }
        else{
            this->setWindowTitle(name.mid(this->_cstrct, this->_tstrl));
            this->_cstrct--;
            if(this->_cstrct <= 0)
                this->_revscr = false;
        }
    }
    else{
        this->setWindowTitle(name);
    }
}
void MainWindow::toggleEQ()
{
    if(!this->eq->isHidden())
    {
        this->eq->hide();
        this->ui->pushButton_4->setStyleSheet("color: blue;");
    }
    else
    {
        this->eq->show();
        this->ui->pushButton_4->setStyleSheet("color: red;");
    }
}
void MainWindow::togglePL(){
    if(this->playlist->isVisible()){
        this->playlist->hide();
        this->ui->pushButton_5->setStyleSheet("color: blue;");
    }
    else{
        this->playlist->show();
        this->ui->pushButton_5->setStyleSheet("color: red;");
    }
}
void MainWindow::showEq(bool vis){
    if(vis){
        this->eq->show();
        this->ui->pushButton_4->setStyleSheet("color: red;");
    }
    else{
        this->eq->hide();
        this->ui->pushButton_4->setStyleSheet("color: blue;");
    }
}
void MainWindow::showPl(bool vis){
    if(vis){
        this->playlist->show();
        this->ui->pushButton_5->setStyleSheet("color: red;");
    }
    else{
        this->playlist->hide();
        this->ui->pushButton_5->setStyleSheet("color: blue;");
    }
}
void MainWindow::setStyle(QString file){
    QFile f(file);
    if(f.exists() && f.open(QIODevice::ReadOnly)){
        this->setStyleSheet((*new QString(f.readAll())));
        f.close();
        return;
    }
    qDebug() << "stylesheet file not found...";
}
void MainWindow::showVis(bool vis){
    if(vis){
        this->vis->show();
        this->ui->pushButton_6->setStyleSheet("color: red;");
    }
    else{
        this->vis->hide();
        this->ui->pushButton_6->setStyleSheet("color: blue;");
    }
}
void MainWindow::toggleVis(){
    if(this->vis->isVisible()){
        this->vis->hide();
        this->ui->pushButton_6->setStyleSheet("color: blue;");
    }
    else{
        this->vis->show();
        this->ui->pushButton_6->setStyleSheet("color: red;");
    }
}
void MainWindow::turnShuffle(){
    qDebug() << "turn shuffle...";
}
void MainWindow::setRepeat(){
    qDebug() << "set repeat";
}