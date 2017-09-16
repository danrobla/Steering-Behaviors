#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adjustdialog.h"
#include "ui_adjustdialog.h"
#include "SteeringBehaviors/ParamLoader.h"
#include "QGraphicsDropShadowEffect"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dialog = new AdjustDialog(this->ui->widget);
    ui->action_Prioritized->setChecked(true);
    if(!Prm.wander()){ui->action_Wander_Circle->setDisabled(true);}
    if(!Prm.wall_avoidance()){ui->actionFeelers->setDisabled(true);}
    if(!Prm.follow_path()){ui->action_Path->setDisabled(true);}
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Quit_triggered()
{
    closeWindow();
}

void MainWindow::closeWindow()
{
    close();
}

void MainWindow::openDialog()
{
    dialog->setModal(false);
    dialog->show();
}

void MainWindow::on_action_Obstacles_triggered()
{
    ui->widget->toggleShowObstacles();
}


void MainWindow::on_action_Walls_triggered()
{
    ui->widget->toggleShowWalls();
    ui->actionFeelers->setEnabled(!ui->actionFeelers->isEnabled());
}

void MainWindow::on_action_Weighted_Sum_triggered()
{
    ui->widget->switchWeightedSum();
    ui->action_Weighted_Sum->setChecked(true);
    ui->action_Prioritized->setChecked(false);
    ui->action_Dithered->setChecked(false);
}


void MainWindow::on_action_Prioritized_triggered()
{
    ui->widget->switchPrioritized();
    ui->action_Weighted_Sum->setChecked(false);
    ui->action_Prioritized->setChecked(true);
    ui->action_Dithered->setChecked(false);
}


void MainWindow::on_action_Dithered_triggered()
{
    ui->widget->switchDithered();
    ui->action_Weighted_Sum->setChecked(false);
    ui->action_Prioritized->setChecked(false);
    ui->action_Dithered->setChecked(true);
}


void MainWindow::on_action_Keys_triggered()
{
    ui->widget->toggleShowKeys();
}

void MainWindow::on_action_FPS_triggered()
{
    ui->widget->toggleShowFPS();
}

void MainWindow::on_action_Smoothing_triggered()
{
    ui->widget->toggleSmoothing();
}

void MainWindow::on_action_Adjust_Levels_triggered()
{
    openDialog();
}

void MainWindow::on_action_Wander_Circle_triggered()
{
    ui->widget->toggleShowWanderCircle();
}

void MainWindow::on_action_Detection_Box_triggered()
{
    ui->widget->toggleShowDetectionBox();
}

void MainWindow::on_actionFeelers_triggered()
{
    ui->widget->toggleShowFeelers();
}

void MainWindow::on_action_Steering_Force_triggered()
{
    ui->widget->toggleShowSteeringForce();
}
