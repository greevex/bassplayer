#include "openurl.h"
#include "ui_openurl.h"

OpenUrl::OpenUrl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenUrl)
{
    ui->setupUi(this);
    connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(ok()));
    connect(this->ui->pushButton_2, SIGNAL(clicked()), this, SLOT(cancel()));
}
QString OpenUrl::getURL(){
    return this->ui->lineEdit->text();
}

OpenUrl::~OpenUrl()
{
    delete ui;
}

void OpenUrl::changeEvent(QEvent *e)
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
void OpenUrl::ok(){
    this->okPressed();
}
void OpenUrl::cancel(){
    this->canceled();
}
