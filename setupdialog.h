#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>
#include "SteeringBehaviors/ParamLoader.h"

namespace Ui {
class SetupDialog;
}

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupDialog(QWidget *parent = 0);
    ~SetupDialog();

private slots:
    void setNumAgents(int n);
    void setNumObstacles(int n);
    void setMinObstacleRadius(double n);
    void setMaxObstacleRadius(double n);
    void setNumCellsX(int n);
    void setNumCellsY(int n);
    void setNumSamplesForSmoothing(int n);
    void setSteeringForceTweaker(double n);
    void setSteeringForce(double n);
    void setMaxSpeed(double n);
    void setVehicleMass(double n);
    void setVehicleScale(double n);
    void toggleSeek();
    void toggleFlee();
    void toggleArrive();
    void toggleWander();
    void toggleCohesion();
    void toggleSeparation();
    void toggleAllignment();
    void toggleObstacleAvoidance();
    void toggleWallAvoidance();
    void toggleFollowPath();
    void togglePursuit();
    void toggleEvade();
    void toggleInterpose();
    void toggleHide();
    void toggleFlocking();
    void toggleOffsetPursuit();
    void toggleShoal();

private:
    Ui::SetupDialog *ui;
};

#endif // SETUPDIALOG_H
