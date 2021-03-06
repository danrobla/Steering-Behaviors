#ifndef GameWorld_H
#define GameWorld_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name:   GameWorld.h
//
//  Desc:   All the environment data and methods for the Steering
//          Behavior projects. This class is the root of the project's
//          update and render calls (excluding main of course)
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <vector>

#include "2D/Vector2D.h"
#include "misc/CellSpacePartition.h"
#include "EntityFunctionTemplates.h"
#include "Vehicle.h"

class Obstacle;
class Wall2D;
class Path;
class QMouseEvent;
class QKeyEvent;


typedef std::vector<BaseGameEntity*>::iterator  ObIt;


class GameWorld
{
private:

  //a container of all the moving entities
  std::vector<Vehicle*>         m_Vehicles;

  //any obstacles
  std::vector<BaseGameEntity*>  m_Obstacles;

  //container containing any walls in the environment
  std::vector<Wall2D>           m_Walls;

  CellSpacePartition<Vehicle*>* m_pCellSpace;

  //any path we may create for the vehicles to follow
  Path*                         m_pPath;

  //set true to pause the motion
  bool                          m_bPaused;

  //local copy of client window dimensions
  int                           m_cxClient,
                                m_cyClient;
  //the position of the crosshair
  Vector2D                      m_vCrosshair;

  //keeps track of the average FPS
  double                        m_dAvFrameTime;

  //flags to turn aids and obstacles etc on/off
  bool  m_bShowWalls;
  bool  m_bShowObstacles;
  bool  m_bShowPath;
  bool  m_bShowDetectionBox;
  bool  m_bShowWanderCircle;
  bool  m_bShowFeelers;
  bool  m_bShowSteeringForce;
  bool  m_bShowFPS;
  bool  m_bRenderNeighbors;
  bool  m_bViewKeys;
  bool  m_bShowCellSpaceInfo;


  void CreateObstacles();

  void CreateWalls();



public:

  GameWorld(int cx, int cy);

  ~GameWorld();

  void  Update(double time_elapsed);

  void  Render();


  void  NonPenetrationContraint(Vehicle* v){EnforceNonPenetrationConstraint(v, m_Vehicles);}

  void  TagVehiclesWithinViewRange(BaseGameEntity* pVehicle, double range)
  {
    TagNeighbors(pVehicle, m_Vehicles, range);
  }

  void  TagObstaclesWithinViewRange(BaseGameEntity* pVehicle, double range)
  {
    TagNeighbors(pVehicle, m_Obstacles, range);
  }

  const std::vector<Wall2D>&          Walls(){return m_Walls;}
  CellSpacePartition<Vehicle*>*       CellSpace(){return m_pCellSpace;}
  const std::vector<BaseGameEntity*>& Obstacles()const{return m_Obstacles;}
  const std::vector<Vehicle*>&        Agents(){return m_Vehicles;}

  void        HandleKeyPresses(QKeyEvent* e);
  void        HandleVehicleEvents(QKeyEvent* e);

  void        TogglePause(){m_bPaused = !m_bPaused;}
  bool        Paused()const{return m_bPaused;}

  Vector2D    Crosshair()const{return m_vCrosshair;}
  void        SetCrosshair(Vector2D v);
  void        SetCrosshair(QMouseEvent *e);

  int   cxClient()const{return m_cxClient;}
  int   cyClient()const{return m_cyClient;}
  void  cxClientSet(int cx){m_cxClient = cx;}
  void  cyClientSet(int cy){m_cyClient = cy;}

  bool  RenderWalls()const{return m_bShowWalls;}
  bool  RenderObstacles()const{return m_bShowObstacles;}
  bool  RenderPath()const{return m_bShowPath;}
  bool  RenderDetectionBox()const{return m_bShowDetectionBox;}
  bool  RenderWanderCircle()const{return m_bShowWanderCircle;}
  bool  RenderFeelers()const{return m_bShowFeelers;}
  bool  RenderSteeringForce()const{return m_bShowSteeringForce;}

  bool  RenderFPS()const{return m_bShowFPS;}
  void  ToggleShowFPS(){m_bShowFPS = !m_bShowFPS;}

  void  ToggleRenderNeighbors(){m_bRenderNeighbors = !m_bRenderNeighbors;}
  bool  RenderNeighbors()const{return m_bRenderNeighbors;}

  void  ToggleViewKeys(){m_bViewKeys = !m_bViewKeys;}
  bool  ViewKeys()const{return m_bViewKeys;}
  void  toggleSmoothing();
  void  changeMaxSteeringForce(double);
  void  changeMaxSpeed(double s);
  void  changeWanderJitter(double w);
  void  changeWanderDistance(double d);
  void  changeWanderRadius(double d);
  void  toggleShowWanderCircle(){m_bShowWanderCircle=!m_bShowWanderCircle;}
  void  toggleShowDetectionBox(){m_bShowDetectionBox=!m_bShowDetectionBox;}
  void  toggleShowFeelers(){m_bShowFeelers=!m_bShowFeelers;}
  void  toggleShowSteeringForce(){m_bShowSteeringForce=!m_bShowSteeringForce;}
  void  toggleShowObstacles();
  void  toggleShowWalls();
  void  switchWeightedSum();
  void  switchPrioritized();
  void  switchDithered();
  void  changeSeparationWeight(double w);
  void  changeAlignmentWeight(double w);
  void  changeCohesionWeight(double w);
};



#endif
