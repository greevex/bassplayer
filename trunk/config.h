#ifndef CONFIG_H
#define CONFIG_H

#include <QApplication>
#include <QDebug>

#define PATH                         QCoreApplication::applicationDirPath()
#define URLCHEME                "http"
#define SELECTEDCOLOR      QColor(0x90, 0x40, 0x10)
#define NORMALCOLOR         QColor(0xcc, 0xcc, 0xff)

#define err qDebug() << "error:"

#define FPS 40

#endif // CONFIG_H
