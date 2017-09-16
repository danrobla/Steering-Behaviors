#include "adjustdialog.h"
#include "ui_adjustdialog.h"
#include "SteeringBehaviors/ParamLoader.h"

AdjustDialog::AdjustDialog(GLWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdjustDialog)
{
    ui->setupUi(this);
    parentwidget = parent;
    ui->AlignWeight->setRange(0, 50*Prm.SteeringForceTweaker());
    ui->AlignWeight->setValue(1*Prm.SteeringForceTweaker());
    ui->CohesionWeight->setRange(0, 50*Prm.SteeringForceTweaker());
    ui->CohesionWeight->setValue(2*Prm.SteeringForceTweaker());
    ui->SeparationWeight->setRange(0, 50*Prm.SteeringForceTweaker());
    ui->SeparationWeight->setValue(1*Prm.SteeringForceTweaker());
    if(!Prm.allignment()){ui->AlignWeight->setValue(0); ui->AlignWeight->setDisabled(true); ui->AlignWeightLabel->setDisabled(true);}
    if(!Prm.cohesion()){ui->CohesionWeight->setValue(0); ui->CohesionWeight->setDisabled(true); ui->CohesionWeightLabel->setDisabled(true);}
    if(!Prm.separation()){ui->SeparationWeight->setValue(0); ui->SeparationWeight->setDisabled(true); ui->SeparationWeightLabel->setDisabled(true);}
}

AdjustDialog::~AdjustDialog()
{
    delete ui;
}

void AdjustDialog::changeMaxSteeringForce(int b)
{
    parentwidget->changeMaxSteeringForce(b);
}

void AdjustDialog::changeMaxSpeed(int b)
{
    parentwidget->changeMaxSpeed(b);
}

void AdjustDialog::changeWanderJitter(int w)
{
    parentwidget->changeWanderJitter(w);
}

void AdjustDialog::changeWanderDistance(int w)
{
    parentwidget->changeWanderDistance((double)(0.1*w));
}

void AdjustDialog::changeWanderRadius(int w)
{
    parentwidget->changeWanderRadius((double)(0.1*w));
}

void AdjustDialog::changeSeparationWeight(int w)
{
    parentwidget->changeSeparationWeight((double)(0.1*w));
}

void AdjustDialog::changeAlignmentWeight(int w)
{
    parentwidget->changeAlignmentWeight((double)(0.1*w));
}

void AdjustDialog::changeCohesionWeight(int w)
{
    parentwidget->changeCohesionWeight((double)(0.1*w));
}

