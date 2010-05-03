#ifndef CONFIG_H
#define CONFIG_H

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QPainter>

#define PATH                         QCoreApplication::applicationDirPath()
#define URLCHEME                "http"
#define SELECTEDCOLOR      QColor(0x90, 0x40, 0x10)
#define NORMALCOLOR         QColor(0xcc, 0xcc, 0xff)
#define LOCKFILE                  QDir::tempPath() + "/bplay.lock"
#define FILESFILE                QDir::tempPath() + "/bplay.files"
#define PLAYLIST                 "/playlist.m3u"
#define SETTING                  "/setting.ini"
#define STYLE                       "/style.css"
#define VISSETTING            "/vis.ini"
#define PLUGINPATH            PATH + "/plugins/"

#define err                             qDebug() << "error:"

#define FPS 40

#endif // CONFIG_H
