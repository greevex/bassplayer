/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu 8. Apr 07:12:12 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QLabel *label;
    QSlider *horizontalSlider_3;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(367, 85);
        MainWindow->setFocusPolicy(Qt::NoFocus);
        MainWindow->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(210, 20, 32, 32));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(270, 20, 32, 32));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/icons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon1);
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(300, 20, 32, 32));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/icons/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon2);
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setEnabled(true);
        horizontalSlider->setGeometry(QRect(10, 2, 351, 16));
        horizontalSlider->setTracking(true);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider_2 = new QSlider(centralWidget);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setEnabled(true);
        horizontalSlider_2->setGeometry(QRect(10, 20, 131, 16));
        horizontalSlider_2->setMaximum(100);
        horizontalSlider_2->setPageStep(1);
        horizontalSlider_2->setValue(20);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 64, 81, 16));
        label->setStyleSheet(QString::fromUtf8("border-radius:4px;border:1px solid #000;"));
        horizontalSlider_3 = new QSlider(centralWidget);
        horizontalSlider_3->setObjectName(QString::fromUtf8("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(10, 43, 131, 16));
        horizontalSlider_3->setMaximum(20);
        horizontalSlider_3->setPageStep(1);
        horizontalSlider_3->setValue(10);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 40, 21, 16));
        label_2->setTextFormat(Qt::RichText);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(150, 17, 21, 16));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(330, 60, 31, 23));
        pushButton_4->setStyleSheet(QString::fromUtf8("background: none; color: red;"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/res/icons/equalizer.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_4->setIcon(icon3);
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(300, 60, 31, 23));
        pushButton_5->setStyleSheet(QString::fromUtf8("color:red;"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/res/icons/playlist.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon4);
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(270, 60, 31, 23));
        pushButton_6->setStyleSheet(QString::fromUtf8("color: red"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/res/icons/video.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_6->setIcon(icon5);
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(330, 20, 32, 32));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/res/icons/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_7->setIcon(icon6);
        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(240, 20, 32, 32));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/res/icons/prew.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_8->setIcon(icon7);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(180, 27, 16, 16));
        label_4->setStyleSheet(QString::fromUtf8("color: #aaa;"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(195, 27, 21, 16));
        label_5->setStyleSheet(QString::fromUtf8("color: #aaa;"));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton->setToolTip(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273\321\213", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_2->setToolTip(QApplication::translate("MainWindow", "\320\222\320\276\321\201\320\277\321\200\320\276\320\270\320\267\320\262\320\265\321\201\321\202\320\270", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_2->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_3->setToolTip(QApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_3->setText(QString());
        label->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Pan</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Vol", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_4->setToolTip(QApplication::translate("MainWindow", "\320\255\320\272\320\262\320\260\320\273\320\260\320\271\320\267\320\265\321\200", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_4->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_5->setToolTip(QApplication::translate("MainWindow", "\320\237\320\273\320\265\320\271\320\273\320\270\321\201\321\202", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_5->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_6->setToolTip(QApplication::translate("MainWindow", "\320\222\320\270\320\267\321\203\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_6->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_7->setToolTip(QApplication::translate("MainWindow", "\320\222\320\277\320\265\321\200\321\221\320\264", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_7->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_8->setToolTip(QApplication::translate("MainWindow", "\320\235\320\260\320\267\320\260\320\264", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_8->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_4->setToolTip(QApplication::translate("MainWindow", "\320\241\320\273\321\203\321\207\320\260\320\271\320\275\321\213\320\271 \320\277\320\276\321\200\321\217\320\264\320\276\320\272 (\320\222\321\213\320\272\320\273)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("MainWindow", "S", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_5->setToolTip(QApplication::translate("MainWindow", "\320\237\320\276\320\262\321\202\320\276\321\200 (\320\222\321\213\320\272\320\273)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("MainWindow", "R", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
