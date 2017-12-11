/********************************************************************************
** Form generated from reading UI file 'ProjetII.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJETII_H
#define UI_PROJETII_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjetIIClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProjetIIClass)
    {
        if (ProjetIIClass->objectName().isEmpty())
            ProjetIIClass->setObjectName(QStringLiteral("ProjetIIClass"));
        ProjetIIClass->resize(600, 400);
        menuBar = new QMenuBar(ProjetIIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ProjetIIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ProjetIIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ProjetIIClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ProjetIIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ProjetIIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ProjetIIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ProjetIIClass->setStatusBar(statusBar);

        retranslateUi(ProjetIIClass);

        QMetaObject::connectSlotsByName(ProjetIIClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProjetIIClass)
    {
        ProjetIIClass->setWindowTitle(QApplication::translate("ProjetIIClass", "ProjetII", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ProjetIIClass: public Ui_ProjetIIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJETII_H
