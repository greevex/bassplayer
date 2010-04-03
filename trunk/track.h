#ifndef TRACK_H
#define TRACK_H
#include <Qt>
class Track
{
public:
    Track(QString path);
    Track(bool b);
    QString *path;
    QString *name;
    QString *type;
};

#endif // TRACK_H
