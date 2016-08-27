/********************************************************************************
** Form generated from reading UI file 'fclog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FCLOG_H
#define UI_FCLOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FCLog
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *FCLog)
    {
        if (FCLog->objectName().isEmpty())
            FCLog->setObjectName(QStringLiteral("FCLog"));
        FCLog->resize(400, 300);
        verticalLayout = new QVBoxLayout(FCLog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textEdit = new QTextEdit(FCLog);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(FCLog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(FCLog);
        QObject::connect(pushButton, SIGNAL(clicked()), FCLog, SLOT(hide()));

        QMetaObject::connectSlotsByName(FCLog);
    } // setupUi

    void retranslateUi(QDialog *FCLog)
    {
        FCLog->setWindowTitle(QApplication::translate("FCLog", "Log Window", 0));
        pushButton->setText(QApplication::translate("FCLog", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class FCLog: public Ui_FCLog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FCLOG_H
