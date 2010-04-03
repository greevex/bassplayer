/********************************************************************************
** Form generated from reading UI file 'vis.ui'
**
** Created: Fri 2. Apr 19:05:45 2010
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
        Vis->resize(256, 192);

        retranslateUi(Vis);

        QMetaObject::connectSlotsByName(Vis);
    } // setupUi

    void retranslateUi(QDialog *Vis)
    {
        Vis->setWindowTitle(QApplication::translate("Vis", "Spectr", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Vis: public Ui_Vis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIS_H
