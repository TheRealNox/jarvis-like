/********************************************************************************
** Form generated from reading UI file 'jarvis.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JARVIS_H
#define UI_JARVIS_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JarvisClass
{
public:
    QAction *actionExit;
    QAction *actionVoiceSettings;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *JarvisClass)
    {
        if (JarvisClass->objectName().isEmpty())
            JarvisClass->setObjectName(QStringLiteral("JarvisClass"));
        JarvisClass->resize(600, 400);
        JarvisClass->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionExit = new QAction(JarvisClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionVoiceSettings = new QAction(JarvisClass);
        actionVoiceSettings->setObjectName(QStringLiteral("actionVoiceSettings"));
        centralWidget = new QWidget(JarvisClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        JarvisClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(JarvisClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        JarvisClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(JarvisClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        JarvisClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuTools->addAction(actionVoiceSettings);

        retranslateUi(JarvisClass);

        QMetaObject::connectSlotsByName(JarvisClass);
    } // setupUi

    void retranslateUi(QMainWindow *JarvisClass)
    {
        JarvisClass->setWindowTitle(QApplication::translate("JarvisClass", "Jarvis", 0));
        actionExit->setText(QApplication::translate("JarvisClass", "Exit", 0));
        actionVoiceSettings->setText(QApplication::translate("JarvisClass", "Voice Settings", 0));
        menuFile->setTitle(QApplication::translate("JarvisClass", "File", 0));
        menuTools->setTitle(QApplication::translate("JarvisClass", "Tools", 0));
    } // retranslateUi

};

namespace Ui {
    class JarvisClass: public Ui_JarvisClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JARVIS_H
