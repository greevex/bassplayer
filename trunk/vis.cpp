#include "vis.h"
#include "ui_vis.h"
#include <QDebug>
#include <QPainter>

Vis::Vis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vis)
{
    this->setWindowTitle("Spectr");
    this->setWindowFlags(Qt::Tool | Qt::MSWindowsFixedSizeDialogHint);
    this->timer = new QTimer(this);
    this->timer->setInterval(30);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(repaint()));
    this->timer->start();
    for(int i = 0; i < 128; i++){
        this->pik[i] = 0;
    }
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
        QPainter paint(this);
        paint.setPen(QColor(0xc0, 0xc0, 0xf0));
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

            if(h < this->pik[j]){
                this->pik[j] = h - 1;
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
        paint.setPen(QColor(0xff, 0x00, 0x00));
        for(int k = 0; k < 128; k++){
            paint.drawPoint(k * 2, this->pik[k]);
            paint.drawPoint(k * 2 + 1, this->pik[k]);
        }
}
void Vis::drawLine(QPainter &paint, int x, int y1, int y2, int sr, int sg, int sb, int er, int eg, int eb){
    int yi = 1;
    int y3 = y1;
    int tff = 255;
    float gl = (255 / y1) * -1;
    if(y1 > y2){
        yi = -1;
    }
    for(int i = 0; i < 2; i++){
        for(y1; y1 > (y2 + yi); y1+= yi, tff+=gl){
            paint.setPen(QColor(sr, sg, sb, (int)tff));
            paint.drawPoint(x, y1);
            paint.drawPoint(x + 1, y1);
        }
        y1 = y3;
        sr = er;
        sg = eg;
        sb = eb;
        gl = gl * -1;
        tff = 0;
    }
}
