#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class AdjustDialog;
class QGraphicsDropShadowEffect;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_Quit_triggered();
    void on_action_Obstacles_triggered();
    void on_action_Walls_triggered();
    void on_action_Weighted_Sum_triggered();
    void on_action_Prioritized_triggered();
    void on_action_Dithered_triggered();
    void on_action_Keys_triggered();
    void on_action_FPS_triggered();
    void on_action_Smoothing_triggered();
    void on_action_Adjust_Levels_triggered();
    void on_action_Wander_Circle_triggered();
    void on_action_Detection_Box_triggered();
    void on_actionFeelers_triggered();
    void on_action_Steering_Force_triggered();

private slots:
    void closeWindow();
    void openDialog();



private:
    Ui::MainWindow *ui;
    AdjustDialog *dialog;
};

#endif // MAINWINDOW_H
