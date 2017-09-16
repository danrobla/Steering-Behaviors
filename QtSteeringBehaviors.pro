#-------------------------------------------------
#
# Project created by QtCreator 2013-11-10T13:44:13
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtSteeringBehaviors
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    2D/Vector2D.cpp \
    misc/Cgdi.cpp \
    misc/iniFileLoaderBase.cpp \
    misc/PrecisionTimer.cpp \
    SteeringBehaviors/GameWorld.cpp \
    SteeringBehaviors/Obstacle.cpp \
    SteeringBehaviors/ParamLoader.cpp \
    SteeringBehaviors/Path.cpp \
    SteeringBehaviors/SteeringBehaviors.cpp \
    SteeringBehaviors/Vehicle.cpp \
    glwidget.cpp \
    setupdialog.cpp \
    adjustdialog.cpp \
    initialdialog.cpp

HEADERS  += mainwindow.h \
    2D/C2DMatrix.h \
    2D/geometry.h \
    2D/InvertedAABBox2D.h \
    2D/Transformations.h \
    2D/Vector2D.h \
    2D/Wall2D.h \
    2D/WallIntersectionTests.h \
    misc/CellSpacePartition.h \
    misc/Cgdi.h \
    misc/iniFileLoaderBase.h \
    misc/PrecisionTimer.h \
    misc/Smoother.h \
    misc/Stream_Utility_Functions.h \
    misc/utils.h \
    SteeringBehaviors/BaseGameEntity.h \
    SteeringBehaviors/constants.h \
    SteeringBehaviors/EntityFunctionTemplates.h \
    SteeringBehaviors/GameWorld.h \
    SteeringBehaviors/LColor.h \
    SteeringBehaviors/LVertexPos2D.h \
    SteeringBehaviors/MovingEntity.h \
    SteeringBehaviors/Obstacle.h \
    SteeringBehaviors/ParamLoader.h \
    SteeringBehaviors/Path.h \
    SteeringBehaviors/SteeringBehaviors.h \
    SteeringBehaviors/Vehicle.h \
    glwidget.h \
    setupdialog.h \
    adjustdialog.h \
    initialdialog.h

FORMS    += mainwindow.ui \
    setupdialog.ui \
    adjustdialog.ui \
    initialdialog.ui

LIBS     += -lGL -lGLU -lXrandr -lGLEW -lXext -lX11 -lXxf86vm -lrt -lXi -lXinerama -lpthread

OTHER_FILES += \
    params.ini
