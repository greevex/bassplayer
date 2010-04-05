#include "vis.h"
#include "ui_vis.h"
#include <QPainter>

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
    for(int i = 0; i < 128; i++){
        this->pik[i] = 0;
    }
    this->bcol = new QColor(0x00, 0x00, 0x00);
    this->pcol = new QColor(0xff, 0x00, 0x00);
    this->mcol = new QColor(0x00, 0xff, 0x00);
    ui->setupUi(this);
}

Vis::~Vis()
{
    delete ui;
}
void Vis::setChannel(HSTREAM chan){
    this->chan = chan;
}
void Vis::setColor(QColor back, QColor pik, QColor main){
    *(this->bcol) = back;
    *(this->mcol) = main;
    *(this->pcol) = pik;
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
        QPainter paint(this);
        paint.fillRect(0, 0, this->width(), this->height(), *(this->bcol));
        paint.setPen(*(this->mcol));
        BASS_ChannelGetData(this->chan, fft, BASS_DATA_FFT4096); //получение даных БФП
        float c = 0;
        int h = 0;
        int j1 = 0;
        for(int i = 0, j = 0; i < 1024; i+=8, j++){
            for(int l = 0; l < 8; l+=2){
                c += fft[i+l];
            }
            c = c / 4; //вычисление среднего из 4х "соседних частот"
            h = (int)(this->height() - (c * 10 * this->height() * 3));
            if(h < (this->height() / 2)){
                h = (int)((this->height() / 2) + (h / 10)); //"урезание"
            }

            if(h <= this->pik[j]){
                this->pik[j] = h - 2;
            }

            j1 = j * 2;
            paint.drawLine(j1, this->height(), j1, h);
            j1++;
            paint.drawLine(j1, this->height(), j1, h);

            c = 0;
        }

        for(int k = 0; k < 128; k++){
            this->pik[k]+=2;
        }
        paint.setPen(*(this->pcol));
        for(int k = 0; k < 128; k++){
            paint.drawLine(k * 2 + 1, this->pik[k], k * 2 + 2, this->pik[k+1]);
            //paint.drawPoint(k * 2, this->pik[k]);
            //paint.drawPoint(k * 2 + 1, this->pik[k]);
        }
        delete fft;
    }
    else{
        this->fps = 1;
        this->timer->setInterval((int)(1000 / this->fps));
    }
}
