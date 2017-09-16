#ifndef ADJUSTDIALOG_H
#define ADJUSTDIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include "glwidget.h"

namespace Ui {
class AdjustDialog;
}

class AdjustDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdjustDialog(GLWidget *parent = 0);
    ~AdjustDialog();

private:
    Ui::AdjustDialog *ui;
    GLWidget* parentwidget;

private slots:
    void changeMaxSteeringForce(int);
    void changeMaxSpeed(int);
    void changeWanderJitter(int);
    void changeWanderDistance(int);
    void changeWanderRadius(int);
    void changeSeparationWeight(int w);
    void changeAlignmentWeight(int w);
    void changeCohesionWeight(int w);
};

#endif // ADJUSTDIALOG_H
