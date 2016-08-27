/********************************************************************************
** Form generated from reading UI file 'fcabout.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FCABOUT_H
#define UI_FCABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FCAbout
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *FCAbout)
    {
        if (FCAbout->objectName().isEmpty())
            FCAbout->setObjectName(QStringLiteral("FCAbout"));
        FCAbout->resize(301, 338);
        FCAbout->setMinimumSize(QSize(301, 338));
        FCAbout->setMaximumSize(QSize(301, 338));
        verticalLayout_2 = new QVBoxLayout(FCAbout);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        label = new QLabel(FCAbout);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(231, 239));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/AMSATFoxLogo.png")));
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(FCAbout);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        label_5 = new QLabel(FCAbout);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);
        label_5->setOpenExternalLinks(true);

        verticalLayout->addWidget(label_5);

        label_3 = new QLabel(FCAbout);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setOpenExternalLinks(true);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(FCAbout);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);
        label_4->setOpenExternalLinks(true);

        verticalLayout->addWidget(label_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        pushButton = new QPushButton(FCAbout);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_4->addWidget(pushButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(FCAbout);
        QObject::connect(pushButton, SIGNAL(clicked()), FCAbout, SLOT(accept()));

        QMetaObject::connectSlotsByName(FCAbout);
    } // setupUi

    void retranslateUi(QDialog *FCAbout)
    {
        FCAbout->setWindowTitle(QApplication::translate("FCAbout", "About", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("FCAbout", "FoxCom version 0.62  (8/16)", 0));
        label_5->setText(QApplication::translate("FCAbout", "<a href=\"http://ww2.amsat.org/?page_id=468\">Fox Satellite</a> Commanding Software", 0));
        label_3->setText(QApplication::translate("FCAbout", "<html><head/><body><p align=\"center\">Joshua Lynch (KD0OPN) <a href=\"mailto:jlynch@codeposse.com\"><span style=\" text-decoration: underline; color:#0000ff;\">josh@codeposse.com</span></a></p><p align=\"center\">Carl Wick (N3MIM) <a href=\"mailto:cewick70@gmail.com\"><span style=\" text-decoration: underline; color:#0000ff;\">cewick70@gmail.com</span></a></p></body></html>", 0));
        label_4->setText(QApplication::translate("FCAbout", "<a href=\"http://www.amsat.org\">AMSAT.org</a>", 0));
        pushButton->setText(QApplication::translate("FCAbout", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class FCAbout: public Ui_FCAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FCABOUT_H
