#include "eq.h"
#include "ui_eq.h"

Eq::Eq(QWidget *parent) : QDialog(parent), ui(new Ui::Eq)
{
    this->setWindowTitle("Equalizer");
    this->setWindowFlags(Qt::Tool | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    connect(ui->verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_3, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_4, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_5, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_6, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_7, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_8, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_9, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_10, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_11, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_12, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_13, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_14, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_15, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_16, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_17, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_18, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_19, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_20, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_21, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_22, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_23, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_24, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_25, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_26, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_27, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));
    connect(ui->verticalSlider_28, SIGNAL(valueChanged(int)), this, SLOT(setEQ()));

}

Eq::~Eq()
{
    delete ui;
}

void Eq::changeEvent(QEvent *e)
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
int Eq::getEq(int Hz)
{
    switch(Hz)
    {
    case 80:
        return ui->verticalSlider->value();
    case 120:
        return ui->verticalSlider_2->value();
    case 150:
        return ui->verticalSlider_3->value();
    case 200:
        return ui->verticalSlider_4->value();
    case 250:
        return ui->verticalSlider_5->value();
    case 300:
        return ui->verticalSlider_6->value();
    case 400:
        return ui->verticalSlider_7->value();
    case 500:
        return ui->verticalSlider_8->value();
    case 600:
        return ui->verticalSlider_9->value();
    case 700:
        return ui->verticalSlider_10->value();
    case 800:
        return ui->verticalSlider_11->value();
    case 900:
        return ui->verticalSlider_12->value();
    case 1000:
        return ui->verticalSlider_13->value();
    case 2000:
        return ui->verticalSlider_14->value();
    case 3000:
        return ui->verticalSlider_15->value();
    case 4000:
        return ui->verticalSlider_16->value();
    case 5000:
        return ui->verticalSlider_17->value();
    case 6000:
        return ui->verticalSlider_18->value();
    case 7000:
        return ui->verticalSlider_19->value();
    case 8000:
        return ui->verticalSlider_20->value();
    case 9000:
        return ui->verticalSlider_21->value();
    case 10000:
        return ui->verticalSlider_22->value();
    case 11000:
        return ui->verticalSlider_23->value();
    case 12000:
        return ui->verticalSlider_24->value();
    case 13000:
        return ui->verticalSlider_25->value();
    case 14000:
        return ui->verticalSlider_26->value();
    case 15000:
        return ui->verticalSlider_27->value();
    case 16000:
        return ui->verticalSlider_28->value();
    default:
        return 0;
    }
}
void Eq::setEq(int Hz, int value)
{
    switch(Hz)
    {
    case 80:
        ui->verticalSlider->setValue(value);
    case 120:
        ui->verticalSlider_2->setValue(value);
    case 150:
        ui->verticalSlider_3->setValue(value);
    case 200:
        ui->verticalSlider_4->setValue(value);
    case 250:
        ui->verticalSlider_5->setValue(value);
    case 300:
        ui->verticalSlider_6->setValue(value);
    case 400:
        ui->verticalSlider_7->setValue(value);
    case 500:
        ui->verticalSlider_8->setValue(value);
    case 600:
        ui->verticalSlider_9->setValue(value);
    case 700:
        ui->verticalSlider_10->setValue(value);
    case 800:
        ui->verticalSlider_11->setValue(value);
    case 900:
        ui->verticalSlider_12->setValue(value);
    case 1000:
        ui->verticalSlider_13->setValue(value);
    case 2000:
        ui->verticalSlider_14->setValue(value);
    case 3000:
        ui->verticalSlider_15->setValue(value);
    case 4000:
        ui->verticalSlider_16->setValue(value);
    case 5000:
        ui->verticalSlider_17->setValue(value);
    case 6000:
        ui->verticalSlider_18->setValue(value);
    case 7000:
        ui->verticalSlider_19->setValue(value);
    case 8000:
        ui->verticalSlider_20->setValue(value);
    case 9000:
        ui->verticalSlider_21->setValue(value);
    case 10000:
        ui->verticalSlider_22->setValue(value);
    case 11000:
        ui->verticalSlider_23->setValue(value);
    case 12000:
        ui->verticalSlider_24->setValue(value);
    case 13000:
        ui->verticalSlider_25->setValue(value);
    case 14000:
        ui->verticalSlider_26->setValue(value);
    case 15000:
        ui->verticalSlider_27->setValue(value);
    case 16000:
        ui->verticalSlider_28->setValue(value);
    default:
        break;
    }
}

void Eq::setEQ()
{
    BASS_DX8_PARAMEQ *p80 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p120 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p150 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p200 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p250 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p300 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p400 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p500 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p600 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p700 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p800 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p900 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p1000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p2000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p3000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p4000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p5000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p6000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p7000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p8000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p9000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p10000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p11000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p12000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p13000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p14000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p15000 = new BASS_DX8_PARAMEQ();
    BASS_DX8_PARAMEQ *p16000 = new BASS_DX8_PARAMEQ();
    //// 80 Hz
    p80->fBandwidth = 20;
    p80->fCenter = 80;
    p80->fGain = this->getGain(this->ui->verticalSlider->value());
    ////120 Hz
    p120->fBandwidth = 10;
    p120->fCenter = 120;
    p120->fGain = this->getGain(this->ui->verticalSlider_2->value());
    ////150 Hz
    p150->fBandwidth = 10;
    p150->fCenter = 150;
    p150->fGain = this->getGain(this->ui->verticalSlider_3->value());
    ////200 Hz
    p200->fBandwidth = 10;
    p200->fCenter = 200;
    p200->fGain = this->getGain(this->ui->verticalSlider_4->value());
    ////250 Hz
    p250->fBandwidth = 10;
    p250->fCenter = 250;
    p250->fGain = this->getGain(this->ui->verticalSlider_5->value());
    ////300 Hz
    p300->fBandwidth = 10;
    p300->fCenter = 300;
    p300->fGain = this->getGain(this->ui->verticalSlider_6->value());
    ////400 Hz
    p400->fBandwidth = 10;
    p400->fCenter = 400;
    p400->fGain = this->getGain(this->ui->verticalSlider_7->value());
    ///500 Hz
    p500->fBandwidth = 10;
    p500->fCenter = 500;
    p500->fGain = this->getGain(this->ui->verticalSlider_8->value());
    ////600 Hz
    p600->fBandwidth = 10;
    p600->fCenter = 600;
    p600->fGain = this->getGain(this->ui->verticalSlider_9->value());
    ////700 Hz
    p700->fBandwidth = 10;
    p700->fCenter = 700;
    p700->fGain = this->getGain(this->ui->verticalSlider_10->value());
    ////800 Hz
    p800->fBandwidth = 10;
    p800->fCenter = 800;
    p800->fGain = this->getGain(this->ui->verticalSlider_11->value());
    ////900 Hz
    p900->fBandwidth= 10;
    p900->fCenter = 900;
    p900->fGain = this->getGain(this->ui->verticalSlider_12->value());
    ////1 kHz
    p1000->fBandwidth = 10;
    p1000->fCenter = 1000;
    p1000->fGain = this->getGain(this->ui->verticalSlider_13->value());
    ////2 kHz
    p2000->fBandwidth = 10;
    p2000->fCenter = 2000;
    p2000->fGain = this->getGain(this->ui->verticalSlider_14->value());
    ////3 kHz
    p3000->fBandwidth = 10;
    p3000->fCenter = 3000;
    p3000->fGain = this->getGain(this->ui->verticalSlider_15->value());
    ////4 kHz
    p4000->fBandwidth = 10;
    p4000->fCenter = 4000;
    p4000->fGain = this->getGain(this->ui->verticalSlider_16->value());
    ////5 kHz
    p5000->fBandwidth = 10;
    p5000->fCenter = 5000;
    p5000->fGain = this->getGain(this->ui->verticalSlider_17->value());
    ////6 kHz
    p6000->fBandwidth = 10;
    p6000->fCenter = 6000;
    p6000->fGain = this->getGain(this->ui->verticalSlider_18->value());
    ////7 kHz
    p7000->fBandwidth = 10;
    p7000->fCenter = 7000;
    p7000->fGain = this->getGain(this->ui->verticalSlider_19->value());
    ////8 kHz
    p8000->fBandwidth = 10;
    p8000->fCenter = 8000;
    p8000->fGain = this->getGain(this->ui->verticalSlider_20->value());
    ////9 kHz
    p9000->fBandwidth = 10;
    p9000->fCenter = 9000;
    p9000->fGain = this->getGain(this->ui->verticalSlider_21->value());
    ////10 kHz
    p10000->fBandwidth = 10;
    p10000->fCenter = 10000;
    p10000->fGain = this->getGain(this->ui->verticalSlider_22->value());
    ////11 kHz
    p11000->fBandwidth = 10;
    p11000->fCenter = 11000;
    p11000->fGain = this->getGain(this->ui->verticalSlider_23->value());
    ////12 kHz
    p12000->fBandwidth = 10;
    p12000->fCenter = 12000;
    p12000->fGain = this->getGain(this->ui->verticalSlider_24->value());
    ////13 kHz
    p13000->fBandwidth = 10;
    p13000->fCenter = 13000;
    p13000->fGain = this->getGain(this->ui->verticalSlider_25->value());
    ////14 kHz
    p14000->fBandwidth = 10;
    p14000->fCenter = 14000;
    p14000->fGain = this->getGain(this->ui->verticalSlider_26->value());
    ////15 kHz
    p15000->fBandwidth = 10;
    p15000->fCenter = 15000;
    p15000->fGain = this->getGain(this->ui->verticalSlider_27->value());
    ////16 kHz
    p16000->fBandwidth = 10;
    p16000->fCenter = 16000;
    p16000->fGain = this->getGain(this->ui->verticalSlider_28->value());
    //
    BASS_FXSetParameters(this->e80, p80);
    BASS_FXSetParameters(this->e120, p120);
    BASS_FXSetParameters(this->e150, p150);
    BASS_FXSetParameters(this->e200, p200);
    BASS_FXSetParameters(this->e250, p250);
    BASS_FXSetParameters(this->e300, p300);
    BASS_FXSetParameters(this->e400, p400);
    BASS_FXSetParameters(this->e500, p500);
    BASS_FXSetParameters(this->e600, p600);
    BASS_FXSetParameters(this->e700, p700);
    BASS_FXSetParameters(this->e800, p800);
    BASS_FXSetParameters(this->e900, p900);
    BASS_FXSetParameters(this->e1000, p1000);
    BASS_FXSetParameters(this->e2000, p2000);
    BASS_FXSetParameters(this->e3000, p3000);
    BASS_FXSetParameters(this->e4000, p4000);
    BASS_FXSetParameters(this->e5000, p5000);
    BASS_FXSetParameters(this->e6000, p6000);
    BASS_FXSetParameters(this->e7000, p7000);
    BASS_FXSetParameters(this->e8000, p8000);
    BASS_FXSetParameters(this->e9000, p9000);
    BASS_FXSetParameters(this->e10000, p10000);
    BASS_FXSetParameters(this->e11000, p11000);
    BASS_FXSetParameters(this->e12000, p12000);
    BASS_FXSetParameters(this->e13000, p13000);
    BASS_FXSetParameters(this->e14000, p14000);
    BASS_FXSetParameters(this->e15000, p15000);
    BASS_FXSetParameters(this->e16000, p16000);
    delete p80;
    delete p120;
    delete p150;
    delete p200;
    delete p250;
    delete p300;
    delete p400;
    delete p500;
    delete p600;
    delete p700;
    delete p800;
    delete p900;
    delete p1000;
    delete p2000;
    delete p3000;
    delete p4000;
    delete p5000;
    delete p6000;
    delete p7000;
    delete p8000;
    delete p9000;
    delete p10000;
    delete p11000;
    delete p12000;
    delete p13000;
    delete p14000;
    delete p15000;
    delete p16000;
}
void Eq::setEq()
{
    this->setEQ();
}
float Eq::getGain(int val){
    return (float)((val - 150) / 10);
}
