/********************************************************************************
** Form generated from reading UI file 'fcmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FCMAINWINDOW_H
#define UI_FCMAINWINDOW_H

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

class Ui_FCMainWindow
{
public:
    QAction *actionLog;
    QAction *actionPreferences;
    QAction *actionAbout_FoxCom;
    QAction *actionQuit;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuEdit;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FCMainWindow)
    {
        if (FCMainWindow->objectName().isEmpty())
            FCMainWindow->setObjectName(QStringLiteral("FCMainWindow"));
        FCMainWindow->resize(361, 214);
        FCMainWindow->setMinimumSize(QSize(361, 214));
        actionLog = new QAction(FCMainWindow);
        actionLog->setObjectName(QStringLiteral("actionLog"));
        actionLog->setMenuRole(QAction::NoRole);
        actionPreferences = new QAction(FCMainWindow);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        actionPreferences->setMenuRole(QAction::PreferencesRole);
        actionAbout_FoxCom = new QAction(FCMainWindow);
        actionAbout_FoxCom->setObjectName(QStringLiteral("actionAbout_FoxCom"));
        actionAbout_FoxCom->setMenuRole(QAction::AboutRole);
        actionQuit = new QAction(FCMainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionQuit->setMenuRole(QAction::QuitRole);
        centralWidget = new QWidget(FCMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        FCMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FCMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 361, 21));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        FCMainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(FCMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        statusBar->setFont(font);
        FCMainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuEdit->addAction(actionPreferences);
        menuWindow->addAction(actionLog);
        menuHelp->addAction(actionAbout_FoxCom);
        menuFile->addAction(actionQuit);

        retranslateUi(FCMainWindow);

        QMetaObject::connectSlotsByName(FCMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FCMainWindow)
    {
        FCMainWindow->setWindowTitle(QApplication::translate("FCMainWindow", "FoxCom", 0));
        actionLog->setText(QApplication::translate("FCMainWindow", "Log...", 0));
        actionLog->setShortcut(QApplication::translate("FCMainWindow", "Ctrl+L", 0));
        actionPreferences->setText(QApplication::translate("FCMainWindow", "Preferences...", 0));
        actionAbout_FoxCom->setText(QApplication::translate("FCMainWindow", "About FoxCom...", 0));
        actionQuit->setText(QApplication::translate("FCMainWindow", "Exit", 0));
#ifndef QT_NO_TOOLTIP
        actionQuit->setToolTip(QApplication::translate("FCMainWindow", "Exit", 0));
#endif // QT_NO_TOOLTIP
        actionQuit->setShortcut(QApplication::translate("FCMainWindow", "Ctrl+Q", 0));
        menuEdit->setTitle(QApplication::translate("FCMainWindow", "Edit", 0));
        menuWindow->setTitle(QApplication::translate("FCMainWindow", "Window", 0));
        menuHelp->setTitle(QApplication::translate("FCMainWindow", "Help", 0));
        menuFile->setTitle(QApplication::translate("FCMainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class FCMainWindow: public Ui_FCMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FCMAINWINDOW_H
