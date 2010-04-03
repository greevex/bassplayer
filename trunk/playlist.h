#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <Qt>
#include <QList>
#include "track.h"

#define M3U 1

class PlayList
{
public:
    PlayList();
    Track Next();
    Track Prev();
    Track Current();
    int Add(Track *track);
    bool Remove(int index);
    bool Save(QString filename, int type);
    bool Load(QString filename);

    bool shuffle;
    int repeat; //0 - no repeat, 1 - repeat all, 2 - repeat track
private:
    QList<Track*> _playlist;
    int _current;
    int _lenght;
};

#endif // PLAYLIST_H
