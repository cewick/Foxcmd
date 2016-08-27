/********************************************************************************
** Form generated from reading UI file 'fcpreferences.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FCPREFERENCES_H
#define UI_FCPREFERENCES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FCPreferences
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *generalTab;
    QFormLayout *formLayout_3;
    QCheckBox *confirmCheckBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QComboBox *retryBox;
    QWidget *audioTab;
    QFormLayout *formLayout;
    QLabel *label_2;
    QComboBox *outputDevice;
    QLabel *label_5;
    QComboBox *sampleRate;
    QLabel *label_4;
    QComboBox *gainBox;
    QLabel *label_9;
    QComboBox *clockrateBox;
    QWidget *authTab;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *callsign;
    QLabel *label_6;
    QLineEdit *password;
    QWidget *tab;
    QCheckBox *InvBox;

    void setupUi(QDialog *FCPreferences)
    {
        if (FCPreferences->objectName().isEmpty())
            FCPreferences->setObjectName(QStringLiteral("FCPreferences"));
        FCPreferences->resize(400, 318);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FCPreferences->sizePolicy().hasHeightForWidth());
        FCPreferences->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(FCPreferences);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(FCPreferences);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(FCPreferences);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        tabWidget = new QTabWidget(FCPreferences);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        generalTab = new QWidget();
        generalTab->setObjectName(QStringLiteral("generalTab"));
        formLayout_3 = new QFormLayout(generalTab);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        confirmCheckBox = new QCheckBox(generalTab);
        confirmCheckBox->setObjectName(QStringLiteral("confirmCheckBox"));
        confirmCheckBox->setChecked(true);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, confirmCheckBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(generalTab);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        retryBox = new QComboBox(generalTab);
        retryBox->setObjectName(QStringLiteral("retryBox"));

        horizontalLayout_2->addWidget(retryBox);


        formLayout_3->setLayout(1, QFormLayout::LabelRole, horizontalLayout_2);

        tabWidget->addTab(generalTab, QString());
        audioTab = new QWidget();
        audioTab->setObjectName(QStringLiteral("audioTab"));
        formLayout = new QFormLayout(audioTab);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_2 = new QLabel(audioTab);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        outputDevice = new QComboBox(audioTab);
        outputDevice->setObjectName(QStringLiteral("outputDevice"));

        formLayout->setWidget(0, QFormLayout::FieldRole, outputDevice);

        label_5 = new QLabel(audioTab);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_5);

        sampleRate = new QComboBox(audioTab);
        sampleRate->setObjectName(QStringLiteral("sampleRate"));

        formLayout->setWidget(1, QFormLayout::FieldRole, sampleRate);

        label_4 = new QLabel(audioTab);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        gainBox = new QComboBox(audioTab);
        gainBox->setObjectName(QStringLiteral("gainBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, gainBox);

        label_9 = new QLabel(audioTab);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_9);

        clockrateBox = new QComboBox(audioTab);
        clockrateBox->setObjectName(QStringLiteral("clockrateBox"));

        formLayout->setWidget(4, QFormLayout::FieldRole, clockrateBox);

        tabWidget->addTab(audioTab, QString());
        authTab = new QWidget();
        authTab->setObjectName(QStringLiteral("authTab"));
        formLayout_2 = new QFormLayout(authTab);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(authTab);
        label->setObjectName(QStringLiteral("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        callsign = new QLineEdit(authTab);
        callsign->setObjectName(QStringLiteral("callsign"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, callsign);

        label_6 = new QLabel(authTab);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_6);

        password = new QLineEdit(authTab);
        password->setObjectName(QStringLiteral("password"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, password);

        tabWidget->addTab(authTab, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        InvBox = new QCheckBox(tab);
        InvBox->setObjectName(QStringLiteral("InvBox"));
        InvBox->setGeometry(QRect(50, 30, 111, 17));
        tabWidget->addTab(tab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(FCPreferences);
        QObject::connect(pushButton, SIGNAL(clicked()), FCPreferences, SLOT(accept()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), FCPreferences, SLOT(reject()));

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(FCPreferences);
    } // setupUi

    void retranslateUi(QDialog *FCPreferences)
    {
        FCPreferences->setWindowTitle(QApplication::translate("FCPreferences", "Preferences", 0));
        pushButton_2->setText(QApplication::translate("FCPreferences", "Cancel", 0));
        pushButton->setText(QApplication::translate("FCPreferences", "OK", 0));
        confirmCheckBox->setText(QApplication::translate("FCPreferences", "Confirm before sending command", 0));
        label_3->setText(QApplication::translate("FCPreferences", "Automatic Retries:", 0));
        tabWidget->setTabText(tabWidget->indexOf(generalTab), QApplication::translate("FCPreferences", "General", 0));
        label_2->setText(QApplication::translate("FCPreferences", "Output Device:", 0));
        label_5->setText(QApplication::translate("FCPreferences", "Sample Rate:", 0));
        label_4->setText(QApplication::translate("FCPreferences", "Gain:", 0));
        label_9->setText(QApplication::translate("FCPreferences", "Data Clock:", 0));
        tabWidget->setTabText(tabWidget->indexOf(audioTab), QApplication::translate("FCPreferences", "Audio", 0));
        label->setText(QApplication::translate("FCPreferences", "Callsign:", 0));
        label_6->setText(QApplication::translate("FCPreferences", "Password:", 0));
        tabWidget->setTabText(tabWidget->indexOf(authTab), QApplication::translate("FCPreferences", "Auth", 0));
        InvBox->setText(QApplication::translate("FCPreferences", "Invert Pulse Train", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("FCPreferences", "Invert", 0));
    } // retranslateUi

};

namespace Ui {
    class FCPreferences: public Ui_FCPreferences {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FCPREFERENCES_H
