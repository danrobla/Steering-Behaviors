#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>
#include <QGLWidget>
#include <QTimer>
#include "SteeringBehaviors/GameWorld.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    virtual ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent(QKeyEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

public slots:
    void toggleShowObstacles();
    void toggleShowWalls();
    void switchWeightedSum();
    void switchPrioritized();
    void switchDithered();
    void toggleShowKeys();
    void toggleShowFPS();
    void toggleSmoothing();
    void changeMaxSteeringForce(int f);
    void changeMaxSpeed(int s);
    void changeWanderJitter(int w);
    void toggleShowWanderCircle();
    void toggleShowDetectionBox();
    void toggleShowFeelers();
    void toggleShowSteeringForce();
    void changeWanderDistance(double d);
    void changeWanderRadius(double d);
    void changeCohesionWeight(double d);
    void changeAlignmentWeight(double d);
    void changeSeparationWeight(double d);


protected:
    QTimer *timer;
    GameWorld* g_GameWorld;

};

#endif // GLWIDGET_H
