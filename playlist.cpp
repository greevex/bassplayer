#include "playlist.h"
#include "cstdlib"
#include "time.h"
#include <QFile>
#include <QFileInfo>
PlayList::PlayList()
{
}
int PlayList::Add(Track *track)
{
    this->_playlist.append(track);
    this->_lenght = this->_playlist.length();
    return this->_playlist.lastIndexOf(track);
}
Track PlayList::Next()
{
    switch(this->repeat)
    {
    case 1:
        this->_current++;
        if(this->_current == this->_lenght)
            this->_current = 0;
        if(this->shuffle)
        {
            srand(time(NULL));
            this->_current = rand() % this->_lenght + 1;
            this->_current--;
        }
        return this->_playlist.value(this->_current);
        break;
    case 2:
        return this->_playlist.value(this->_current);
        break;
    case 0:
    default:
        return new Track(false);
        break;
    }
}
Track PlayList::Prev()
{
    switch(this->repeat)
    {
    case 1:
        this->_current--;
        if(this->_current == -1)
            this->_current = this->_lenght - 1;
        if(this->shuffle)
        {
            srand(time(NULL));
            this->_current = rand() % this->_lenght + 1;
            this->_current--;
        }
        return this->_playlist.value(this->_current);
    case 2:
        return this->_playlist.value(this->_current);
        break;
    case 0:
    default:
        return new Track(false);
        break;
    }
}
Track PlayList::Current()
{
    return this->_playlist.value(this->_current);
}
bool PlayList::Remove(int index)
{
    if(index > -1 && index < this->_lenght)
        this->_playlist.removeAt(index);
    else
        return false;
    return true;
}
bool PlayList::Save(QString filename, int type)
{
    QFile *file = new QFile(filename);
    file->open(QIODevice::WriteOnly);
    switch(type)
    {
    case M3U:
        for(int i = 0; i < this->_lenght; i++)
        {
            file->write(this->_playlist.value(i)->path->toLocal8Bit());
            file->write("\n");
        }
        file->close();
        return true;
        break;
    default:
        return false;
    }
}
bool PlayList::Load(QString filename)
{
    QFileInfo *qfi = new QFileInfo(filename);
    if(qfi->suffix().toLower() == "m3u")
    {
        this->_playlist.clear();
        QFile *file = new QFile(filename);
        file->open(QIODevice::ReadOnly);
        while(file->atEnd())
        {
            QString *f = new QString(file->readLine(1024));
            Track *trk = new Track(*f);
            if(trk->type != (QString)"null")
                this->Add(trk);
        }
        file->close();
        file->~QFile();
        qfi->~QFileInfo();
        return true;
    }
}
