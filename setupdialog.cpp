#include "setupdialog.h"
#include "ui_setupdialog.h"
#include "SteeringBehaviors/ParamLoader.h"

SetupDialog::SetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupDialog)
{
    ui->setupUi(this);

    ui->Seek->setChecked(Prm.seek());
    ui->Seek->setEnabled(Prm.singleagent());
    ui->Arrive->setChecked(Prm.arrive());
    ui->Arrive->setEnabled(Prm.singleagent());
    ui->Evade->setChecked(Prm.evade());
    ui->Evade->setEnabled(Prm.singleagent());
    ui->Flee->setChecked(Prm.flee());
    ui->Flee->setEnabled(Prm.singleagent());
    ui->Interpose->setChecked(Prm.interpose());
    ui->Interpose->setEnabled(Prm.singleagent());
    ui->Hide->setChecked(Prm.hide());
    ui->Hide->setEnabled(Prm.singleagent());
    ui->Pursuit->setChecked(Prm.pursuit());
    ui->Pursuit->setEnabled(Prm.singleagent());
    ui->OffsetPursuit->setChecked(Prm.offset_pursuit());
    ui->OffsetPursuit->setEnabled(Prm.singleagent());
    ui->FollowPath->setChecked(Prm.follow_path());
    ui->FollowPath->setEnabled(Prm.singleagent());

    ui->Alignment->setChecked(Prm.allignment());
    ui->Alignment->setDisabled(Prm.flocking() || Prm.singleagent());
    ui->Cohesion->setChecked(Prm.cohesion());
    ui->Cohesion->setDisabled(Prm.flocking() || Prm.singleagent());
    ui->Separation->setChecked(Prm.separation());
    ui->Separation->setDisabled(Prm.flocking() || Prm.singleagent());
    ui->Wander->setChecked(Prm.wander());
    ui->Flock->setChecked(Prm.flocking());
    ui->Flock->setEnabled(Prm.multiagent());
    ui->Shoal->setChecked(Prm.shoal());
    ui->Shoal->setEnabled(Prm.flocking());
}

SetupDialog::~SetupDialog()
{
    delete ui;
}

void SetupDialog::setNumAgents(int n)
{
    Prm.setNumAgents(n);
}

void SetupDialog::setNumObstacles(int n)
{
    Prm.setNumObstacles(n);
}

void SetupDialog::setMinObstacleRadius(double n)
{
    Prm.setMinObstacleRadius(n);
}

void SetupDialog::setMaxObstacleRadius(double n)
{
    Prm.setMaxObstacleRadius(n);
}

void SetupDialog::setNumCellsX(int n)
{
    Prm.setNumCellsX(n);
}

void SetupDialog::setNumCellsY(int n)
{
    Prm.setNumCellsY(n);
}

void SetupDialog::setNumSamplesForSmoothing(int n)
{
    Prm.setNumSamplesForSmoothing(n);
}

void SetupDialog::setSteeringForceTweaker(double n)
{
    Prm.setSteeringForceTweaker(n);
}

void SetupDialog::setSteeringForce(double n)
{
    Prm.setSteeringForce(n);
}

void SetupDialog::setMaxSpeed(double n)
{
    Prm.setMaxSpeed(n);
}

void SetupDialog::setVehicleMass(double n)
{
    Prm.setVehicleMass(n);
}

void SetupDialog::setVehicleScale(double n)
{
    Prm.setVehicleScale(n);
}

void SetupDialog::toggleSeek()
{
    Prm.toggleSeek();
}

void SetupDialog::toggleFlee()
{
    Prm.toggleFlee();
}

void SetupDialog::toggleArrive()
{
    Prm.toggleArrive();
}

void SetupDialog::toggleWander()
{
    Prm.toggleWander();
}

void SetupDialog::toggleCohesion()
{
    Prm.toggleCohesion();
}

void SetupDialog::toggleSeparation()
{
    Prm.toggleSeparation();
}

void SetupDialog::toggleAllignment()
{
    Prm.toggleAllignment();
}

void SetupDialog::toggleObstacleAvoidance()
{
    Prm.toggleObstacleAvoidance();
}

void SetupDialog::toggleWallAvoidance()
{
    Prm.toggleWallAvoidance();
}

void SetupDialog::toggleFollowPath()
{
    Prm.toggleFollowPath();
}

void SetupDialog::togglePursuit()
{
    Prm.togglePursuit();
}

void SetupDialog::toggleEvade()
{
    Prm.toggleEvade();
}

void SetupDialog::toggleInterpose()
{
    Prm.toggleInterpose();
}

void SetupDialog::toggleHide()
{
    Prm.toggleHide();
}

void SetupDialog::toggleFlocking()
{
    Prm.toggleFlocking();
}

void SetupDialog::toggleOffsetPursuit()
{
    Prm.toggleOffsetPursuit();
}

void SetupDialog::toggleShoal()
{
    Prm.toggleShoal();
}
