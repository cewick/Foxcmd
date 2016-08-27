//constructs or deletes a dialog box that passes information
//about the current version (0.6)

#include "fcabout.h"
#include "ui_fcabout.h"

FCAbout::FCAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FCAbout)
{
    ui->setupUi(this);
}

FCAbout::~FCAbout()
{
    delete ui;
}
