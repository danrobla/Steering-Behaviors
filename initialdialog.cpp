#include "initialdialog.h"
#include "ui_initialdialog.h"
#include "SteeringBehaviors/ParamLoader.h"

InitialDialog::InitialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitialDialog)
{
    ui->setupUi(this);
}

InitialDialog::~InitialDialog()
{
    delete ui;
}

void InitialDialog::toggleAgentMode()
{
    Prm.toggleFlocking();
    Prm.toggleSeek();
    Prm.toggleAgentMode();
}

