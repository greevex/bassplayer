#include "track.h"
#include <QFileInfo>

Track::Track(QString path)
{
    QFileInfo *qfi = new QFileInfo(path);
    this->path = (QString*)"";
    this->name = (QString*)"";
    this->type = (QString*)"null";
    if(qfi->exists())
    {
        *this->path = path;
        *this->name = qfi->baseName();
        *this->type = qfi->suffix().toLower();
    }
    qfi->~QFileInfo();
}
Track::Track(bool b)
{}
