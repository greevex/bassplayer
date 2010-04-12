/********************************************************************************
** Form generated from reading UI file 'pl.ui'
**
** Created: Mon 12. Apr 15:36:01 2010
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
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Pl
{
public:
    QListWidget *listWidget;
    QLineEdit *searchInput;
    QPushButton *pushButton;

    void setupUi(QDialog *Pl)
    {
        if (Pl->objectName().isEmpty())
            Pl->setObjectName(QString::fromUtf8("Pl"));
        Pl->resize(300, 263);
        listWidget = new QListWidget(Pl);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 301, 241));
        searchInput = new QLineEdit(Pl);
        searchInput->setObjectName(QString::fromUtf8("searchInput"));
        searchInput->setGeometry(QRect(0, 241, 251, 20));
        pushButton = new QPushButton(Pl);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(250, 240, 51, 23));

        retranslateUi(Pl);

        QMetaObject::connectSlotsByName(Pl);
    } // setupUi

    void retranslateUi(QDialog *Pl)
    {
        Pl->setWindowTitle(QApplication::translate("Pl", "Playlist", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Pl", "Next", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Pl: public Ui_Pl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PL_H
