/********************************************************************************
** Form generated from reading UI file 'pl.ui'
**
** Created: Thu 1. Apr 23:34:01 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PL_H
#define UI_PL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_Pl
{
public:
    QListWidget *listWidget;

    void setupUi(QDialog *Pl)
    {
        if (Pl->objectName().isEmpty())
            Pl->setObjectName(QString::fromUtf8("Pl"));
        Pl->resize(300, 300);
        listWidget = new QListWidget(Pl);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 301, 301));

        retranslateUi(Pl);

        QMetaObject::connectSlotsByName(Pl);
    } // setupUi

    void retranslateUi(QDialog *Pl)
    {
        Pl->setWindowTitle(QApplication::translate("Pl", "Playlist", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Pl: public Ui_Pl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PL_H
