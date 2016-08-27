//This file constructs a dialog that projects information about the current version
//user interface in fcabout.ui
//Version .6 modifications to .5:
//Version change in dialog box
//Added modification author and email to dialog box
//Version change to .61 fixed invert problem due to mainwindow checking all checkboxes including invert
//Version change to .62 changed checkbox poll to just include command window

#ifndef FCABOUT_H
#define FCABOUT_H

#include <QDialog>

namespace Ui {
class FCAbout;
}

class FCAbout : public QDialog
{
    Q_OBJECT
    
public:
    explicit FCAbout(QWidget *parent = 0);
    ~FCAbout();
    
private:
    Ui::FCAbout *ui;
};

#endif // FCABOUT_H
