#-------------------------------------------------
#
# Project created by QtCreator 2013-06-04T01:09:05
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FoxCom
TEMPLATE = app

SOURCES += main.cpp\
        fcmainwindow.cpp \
    fclog.cpp \
    fcpreferences.cpp \
    fcabout.cpp \
    fcencoder.cpp \
    fcrig.cpp \
    fccommand.cpp

HEADERS  += fcmainwindow.h \
    fclog.h \
    fcpreferences.h \
    fcabout.h \
    fcencoder.h \
    fcrig.h \
    fccommand.h

FORMS    += fcmainwindow.ui \
    fclog.ui \
    fcpreferences.ui \
    fcabout.ui

OTHER_FILES += \
    foxcom.rc

RESOURCES += \
    FoxCom.qrc

ICON = foxcom.icns

RC_FILE = foxcom.rc
