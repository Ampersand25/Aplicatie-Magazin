/********************************************************************************
** Form generated from reading UI file 'MagazinGUI.ui'
**
** Created by: Qt User Interface Compiler version 6.0.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAGAZINGUI_H
#define UI_MAGAZINGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MagazinGUIClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MagazinGUIClass)
    {
        if (MagazinGUIClass->objectName().isEmpty())
            MagazinGUIClass->setObjectName(QString::fromUtf8("MagazinGUIClass"));
        MagazinGUIClass->resize(600, 400);
        menuBar = new QMenuBar(MagazinGUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        MagazinGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MagazinGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MagazinGUIClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MagazinGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MagazinGUIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MagazinGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MagazinGUIClass->setStatusBar(statusBar);

        retranslateUi(MagazinGUIClass);

        QMetaObject::connectSlotsByName(MagazinGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *MagazinGUIClass)
    {
        MagazinGUIClass->setWindowTitle(QCoreApplication::translate("MagazinGUIClass", "MagazinGUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MagazinGUIClass: public Ui_MagazinGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAGAZINGUI_H
