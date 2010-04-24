/********************************************************************************
** Form generated from reading UI file 'openurl.ui'
**
** Created: Sun 25. Apr 01:19:44 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENURL_H
#define UI_OPENURL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_OpenUrl
{
public:
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *OpenUrl)
    {
        if (OpenUrl->objectName().isEmpty())
            OpenUrl->setObjectName(QString::fromUtf8("OpenUrl"));
        OpenUrl->resize(304, 70);
        lineEdit = new QLineEdit(OpenUrl);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 10, 264, 20));
        label = new QLabel(OpenUrl);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(3, 12, 31, 16));
        pushButton = new QPushButton(OpenUrl);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(80, 40, 61, 23));
        pushButton_2 = new QPushButton(OpenUrl);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 40, 61, 23));

        retranslateUi(OpenUrl);

        QMetaObject::connectSlotsByName(OpenUrl);
    } // setupUi

    void retranslateUi(QDialog *OpenUrl)
    {
        OpenUrl->setWindowTitle(QApplication::translate("OpenUrl", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("OpenUrl", "URL:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("OpenUrl", "OK", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("OpenUrl", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OpenUrl: public Ui_OpenUrl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENURL_H
