#include "fcmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FCMainWindow w;
    w.show();

    QObject::connect(&a, SIGNAL(aboutToQuit()), &w, SLOT(on_aboutToQuit()));
    
    return a.exec();
}
