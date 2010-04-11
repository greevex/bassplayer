/********************************************************************************
** Form generated from reading UI file 'vis.ui'
**
** Created: Sat 10. Apr 22:51:51 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIS_H
#define UI_VIS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_Vis
{
public:

    void setupUi(QDialog *Vis)
    {
        if (Vis->objectName().isEmpty())
            Vis->setObjectName(QString::fromUtf8("Vis"));
        Vis->resize(320, 240);
        Vis->setMinimumSize(QSize(320, 240));
        Vis->setMaximumSize(QSize(1024, 768));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/icons/plugin.png"), QSize(), QIcon::Normal, QIcon::Off);
        Vis->setWindowIcon(icon);

        retranslateUi(Vis);

        QMetaObject::connectSlotsByName(Vis);
    } // setupUi

    void retranslateUi(QDialog *Vis)
    {
        Vis->setWindowTitle(QApplication::translate("Vis", "Visualization", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Vis: public Ui_Vis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIS_H
