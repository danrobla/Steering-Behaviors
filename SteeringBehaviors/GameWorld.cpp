#include "GameWorld.h"
#include "Vehicle.h"
#include "constants.h"
#include "Obstacle.h"
#include "2D/geometry.h"
#include "2D/Wall2D.h"
#include "2D/Transformations.h"
#include "SteeringBehaviors.h"
#include "misc/Smoother.h"
#include "ParamLoader.h"
#include "misc/Stream_Utility_Functions.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <list>
using std::list;

GameWorld::GameWorld(int cx, int cy):

            m_cxClient(cx),
            m_cyClient(cy),
            m_bPaused(false),
            m_vCrosshair(Vector2D(cxClient()/2.0, cxClient()/2.0)),
            m_bShowWalls(false),
            m_bShowObstacles(false),
            m_bShowPath(false),
            m_bShowWanderCircle(false),
            m_bShowSteeringForce(false),
            m_bShowFeelers(false),
            m_bShowDetectionBox(false),
            m_bShowFPS(false),
            m_dAvFrameTime(0),
            m_pPath(NULL),
            m_bRenderNeighbors(false),
            m_bViewKeys(true),
            m_bShowCellSpaceInfo(false)
{
    m_pCellSpace = new CellSpacePartition<Vehicle*>((double)cx, (double)cy, Prm.NumCellsX(), Prm.NumCellsY(), Prm.NumAgents());

  double border = 30;
  m_pPath = new Path(5, border, border, cx-border, cy-border, true);

  for (int a=0; a<Prm.NumAgents(); ++a)
  {
    Vector2D SpawnPos = Vector2D(cx/2.0+RandomClamped()*cx/2.0,
                                 cy/2.0+RandomClamped()*cy/2.0);


    Vehicle* pVehicle = new Vehicle(this,
                                    SpawnPos,
                                    RandFloat()*TwoPi,
                                    Vector2D(0,0),
                                    Prm.VehicleMass(),
                                    Prm.MaxSteeringForce(),
                                    Prm.MaxSpeed(),
                                    Prm.MaxTurnRatePerSecond(),
                                    Prm.VehicleScale());

    if(Prm.flocking()){pVehicle->Steering()->FlockingOn();}
    if(Prm.seek()){pVehicle->Steering()->SeekOn();}
    if(Prm.flee()){pVehicle->Steering()->FleeOn();}
    if(Prm.arrive()){pVehicle->Steering()->ArriveOn();}
    if(Prm.wander()){pVehicle->Steering()->WanderOn();}
    if(Prm.cohesion()){pVehicle->Steering()->CohesionOn();}
    if(Prm.separation()){pVehicle->Steering()->SeparationOn();}
    if(Prm.allignment()){pVehicle->Steering()->AlignmentOn();}
    if(Prm.obstacle_avoidance()){pVehicle->Steering()->ObstacleAvoidanceOn();}
    if(Prm.wall_avoidance()){pVehicle->Steering()->WallAvoidanceOn();}
    if(Prm.follow_path()){pVehicle->Steering()->FollowPathOn();}

    m_Vehicles.push_back(pVehicle);

    m_pCellSpace->AddEntity(pVehicle);
  }

  if(Prm.shoal())
  {
    m_Vehicles[Prm.NumAgents()-1]->Steering()->FlockingOff();
    m_Vehicles[Prm.NumAgents()-1]->SetScale(Vector2D(10, 10));
    m_Vehicles[Prm.NumAgents()-1]->Steering()->WanderOn();
    m_Vehicles[Prm.NumAgents()-1]->SetMaxSpeed(Prm.MaxSpeed()/2.0);


    for (int i=0; i<Prm.NumAgents()-1; ++i)
    {
        m_Vehicles[i]->Steering()->EvadeOn(m_Vehicles[Prm.NumAgents()-1]);

    }
  }

  if(Prm.evade())
  {
    m_Vehicles[Prm.NumAgents()-1]->Steering()->WanderOn();
    Vector2D size;
    size.x = 3*Prm.VehicleScale();
    size.y = 3*Prm.VehicleScale();
    m_Vehicles[Prm.NumAgents()-1]->SetScale(size);

    for (int i=0; i<Prm.NumAgents()-1; ++i)
    {
        m_Vehicles[i]->Steering()->EvadeOn(m_Vehicles[Prm.NumAgents()-1]);

    }
  }

  if(Prm.hide())
  {
    m_Vehicles[Prm.NumAgents()-1]->Steering()->WanderOn();
    Vector2D size;
    size.x = 3*Prm.VehicleScale();
    size.y = 3*Prm.VehicleScale();
    m_Vehicles[Prm.NumAgents()-1]->SetScale(size);

    for (int i=0; i<Prm.NumAgents()-1; ++i)
    {
        m_Vehicles[i]->Steering()->HideOn(m_Vehicles[Prm.NumAgents()-1]);

    }
  }

  if(Prm.interpose())
  {
    assert(Prm.NumAgents() > 2 && "No interpose possible with two agents only!");
    m_Vehicles[Prm.NumAgents()-1]->Steering()->WanderOn();
    m_Vehicles[Prm.NumAgents()-2]->Steering()->WanderOn();

    Vector2D size;
    size.x = 1.5*Prm.VehicleScale();
    size.y = 1.5*Prm.VehicleScale();

    m_Vehicles[Prm.NumAgents()-2]->SetScale(size);

    for (int i=0; i<Prm.NumAgents()-1; ++i)
    {
        m_Vehicles[i]->Steering()->InterposeOn(m_Vehicles[Prm.NumAgents()-1], m_Vehicles[Prm.NumAgents()-2]);

    }
  }

}



GameWorld::~GameWorld()
{
  for (unsigned int a=0; a<m_Vehicles.size(); ++a)
  {
    delete m_Vehicles[a];
  }

  for (unsigned int ob=0; ob<m_Obstacles.size(); ++ob)
  {
    delete m_Obstacles[ob];
  }

  delete m_pCellSpace;

  delete m_pPath;
}


void GameWorld::Update(double time_elapsed)
{
  if (m_bPaused) return;

  const int SampleRate = 10;
  static Smoother<double> FrameRateSmoother(SampleRate, 0.0);

  m_dAvFrameTime = FrameRateSmoother.Update(time_elapsed);

  for (unsigned int a=0; a<m_Vehicles.size(); ++a)
  {
    m_Vehicles[a]->Update(time_elapsed);
  }
}

void GameWorld::CreateWalls()
{
  double bordersize = 20.0;
  double CornerSize = 0.2;
  double vDist = m_cyClient-2*bordersize;
  double hDist = m_cxClient-2*bordersize;

  const int NumWallVerts = 8;

  Vector2D walls[NumWallVerts] = {Vector2D(hDist*CornerSize+bordersize, bordersize),
                                   Vector2D(m_cxClient-bordersize-hDist*CornerSize, bordersize),
                                   Vector2D(m_cxClient-bordersize, bordersize+vDist*CornerSize),
                                   Vector2D(m_cxClient-bordersize, m_cyClient-bordersize-vDist*CornerSize),

                                   Vector2D(m_cxClient-bordersize-hDist*CornerSize, m_cyClient-bordersize),
                                   Vector2D(hDist*CornerSize+bordersize, m_cyClient-bordersize),
                                   Vector2D(bordersize, m_cyClient-bordersize-vDist*CornerSize),
                                   Vector2D(bordersize, bordersize+vDist*CornerSize)};

  for (int w=0; w<NumWallVerts-1; ++w)
  {
    m_Walls.push_back(Wall2D(walls[w], walls[w+1]));
  }

  m_Walls.push_back(Wall2D(walls[NumWallVerts-1], walls[0]));
}


void GameWorld::CreateObstacles()
{

    for (int o=0; o<Prm.NumObstacles(); ++o)
  {
    bool bOverlapped = true;

    int NumTrys = 0; int NumAllowableTrys = 2000;

    while (bOverlapped)
    {
      NumTrys++;

      if (NumTrys > NumAllowableTrys) return;

      int radius = RandInt((int)Prm.MinObstacleRadius(), (int)Prm.MaxObstacleRadius());

      const int border                 = 10;
      const int MinGapBetweenObstacles = 20;

      BaseGameEntity* ob = new Obstacle(RandInt(radius+border, m_cxClient-radius-border),
                                  RandInt(radius+border, m_cyClient-radius-30-border),
                                  radius);

      if (!Overlapped(ob, m_Obstacles, MinGapBetweenObstacles))
      {        
        m_Obstacles.push_back(ob);

        bOverlapped = false;
      }

      else
      {
        delete ob;
      }
    }
  }
}

void GameWorld::SetCrosshair(Vector2D p)
{
  Vector2D ProposedPosition((double)p.x, (double)p.y);

  for (ObIt curOb = m_Obstacles.begin(); curOb != m_Obstacles.end(); ++curOb)
  {
    if (PointInCircle((*curOb)->Pos(), (*curOb)->BRadius(), ProposedPosition))
    {
      return;
    }

  }
  m_vCrosshair.x = (double)p.x;
  m_vCrosshair.y = (double)p.y;
}

void GameWorld::SetCrosshair(QMouseEvent* e)
{
    Vector2D position;
    position.x = (double) e->x();
    position.y = (double) e->y();

    SetCrosshair(position);
}


void GameWorld::HandleKeyPresses(QKeyEvent* e)
{
    switch(e->key())
    {
        case (Qt::Key_Escape):
        {
            delete m_pPath;
            double border = 60;
            m_pPath = new Path(RandInt(3, 7), border, border, cxClient()-border, cyClient()-border, true);
            m_bShowPath = true;
            for (unsigned int i=0; i<m_Vehicles.size(); ++i)
            {
                m_Vehicles[i]->Steering()->SetPath(m_pPath->GetPath());
            }
            break;
        }


        case (Qt::Key_A):
        {
            TogglePause();
            break;
        }


        case(Qt::Key_O):
        {
            ToggleRenderNeighbors();
            break;
        }

    }
}


void GameWorld::toggleShowObstacles()
{
    m_bShowObstacles = !m_bShowObstacles;

    if (!m_bShowObstacles)
    {
        m_Obstacles.clear();

        for (unsigned int i=0; i<m_Vehicles.size(); ++i)
        {
            m_Vehicles[i]->Steering()->ObstacleAvoidanceOff();
        }

     }
     else
     {
        CreateObstacles();

        for (unsigned int i=0; i<m_Vehicles.size(); ++i)
        {
            m_Vehicles[i]->Steering()->ObstacleAvoidanceOn();
        }
     }
}

void GameWorld::toggleShowWalls()
{
      m_bShowWalls = !m_bShowWalls;

      if (m_bShowWalls)
      {
            CreateWalls();

        for (unsigned int i=0; i<m_Vehicles.size(); ++i)
        {
            m_Vehicles[i]->Steering()->WallAvoidanceOn();
        }

      }

      else
      {
        m_Walls.clear();

        for (unsigned int i=0; i<m_Vehicles.size(); ++i)
        {
          m_Vehicles[i]->Steering()->WallAvoidanceOff();
        }
      }
}

void GameWorld::switchWeightedSum()
{

        for (unsigned int i=0; i<m_Vehicles.size(); ++i)
        {
          m_Vehicles[i]->Steering()->SetSummingMethod(SteeringBehavior::weighted_average);
        }
}

void GameWorld::switchPrioritized()
{

        for (unsigned int i=0; i<m_Vehicles.size(); ++i)
        {
          m_Vehicles[i]->Steering()->SetSummingMethod(SteeringBehavior::prioritized);
        }
}

void GameWorld::switchDithered()
{
        for (unsigned int i=0; i<m_Vehicles.size(); ++i)
        {
          m_Vehicles[i]->Steering()->SetSummingMethod(SteeringBehavior::dithered);
        }
}

void GameWorld::toggleSmoothing()
{
        for (unsigned int i=0; i<m_Vehicles.size(); ++i)
        {
          m_Vehicles[i]->ToggleSmoothing();
        }
}

void GameWorld::changeMaxSteeringForce(double d)
{
    for (unsigned int i=0; i<m_Vehicles.size(); ++i)
    {
        m_Vehicles[i]->Steering()->changeMaxSteeringForce(d);
    }
}

void GameWorld::changeMaxSpeed(double s)
{
    for (unsigned int i=0; i<m_Vehicles.size(); ++i)
    {
        m_Vehicles[i]->Steering()->changeMaxSpeed(s);
    }

    if(Prm.shoal()){m_Vehicles[Prm.NumAgents()-1]->Steering()->changeMaxSpeed(s/2.0);}
}

void GameWorld::changeWanderJitter(double w)
{
    for (unsigned int i=0; i<m_Vehicles.size(); ++i)
    {
        m_Vehicles[i]->Steering()->changeWanderJitter(w);
    }
}

void GameWorld::changeWanderDistance(double w)
{
    for (unsigned int i=0; i<m_Vehicles.size(); ++i)
    {
        m_Vehicles[i]->Steering()->changeWanderDistance(w);
    }
}

void GameWorld::changeWanderRadius(double w)
{
    for (unsigned int i=0; i<m_Vehicles.size(); ++i)
    {
        m_Vehicles[i]->Steering()->changeWanderRadius(w);
    }
}

void  GameWorld::changeSeparationWeight(double w)
{
    for (unsigned int i=0; i<m_Vehicles.size(); ++i)
    {
        m_Vehicles[i]->Steering()->changeSeparationWeight(w);
    }
}

void  GameWorld::changeAlignmentWeight(double w)
{
    for (unsigned int i=0; i<m_Vehicles.size(); ++i)
    {
        m_Vehicles[i]->Steering()->changeAlignmentWeight(w);
    }
}

void  GameWorld::changeCohesionWeight(double w)
{
    for (unsigned int i=0; i<m_Vehicles.size(); ++i)
    {
        m_Vehicles[i]->Steering()->changeCohesionWeight(w);
    }
}


void GameWorld::Render()
{

  gdi->BlackPen();
  for (unsigned int w=0; w<m_Walls.size(); ++w)
  {
    m_Walls[w].Render(true);
  }
  gdi->BlackPen();

  for (unsigned int ob=0; ob<m_Obstacles.size(); ++ob)
  {
    gdi->Circle(m_Obstacles[ob]->Pos(), m_Obstacles[ob]->BRadius());
  }

  for (unsigned int a=0; a<m_Vehicles.size(); ++a)
  {
    m_Vehicles[a]->Render();

    //render cell partitioning stuff
    if (m_bShowCellSpaceInfo && a==0)
    {
      //gdi->HollowBrush();
        InvertedAABBox2D box(m_Vehicles[a]->Pos() - Vector2D(Prm.ViewDistance(), Prm.ViewDistance()),
                             m_Vehicles[a]->Pos() + Vector2D(Prm.ViewDistance(), Prm.ViewDistance()));
      box.Render();

      gdi->RedPen();
      CellSpace()->CalculateNeighbors(m_Vehicles[a]->Pos(), Prm.ViewDistance());
      for (BaseGameEntity* pV = CellSpace()->begin();!CellSpace()->end();pV = CellSpace()->next())
      {
        gdi->Circle(pV->Pos(), pV->BRadius());
      }

      gdi->GreenPen();
      gdi->Circle(m_Vehicles[a]->Pos(), Prm.ViewDistance());
    }
  }

  if(Prm.singleagent())
  {
    gdi->RedPen();
    gdi->Circle(m_vCrosshair, 4);
    gdi->Line(m_vCrosshair.x - 8, m_vCrosshair.y, m_vCrosshair.x + 8, m_vCrosshair.y);
    gdi->Line(m_vCrosshair.x, m_vCrosshair.y - 8, m_vCrosshair.x, m_vCrosshair.y + 8);
  }


  if (RenderPath())
  {
     m_pPath->Render();
  }
/*
  if (RenderFPS())
  {
    gdi->TextColor(Cgdi::grey);
    gdi->TextAtPos(5, cyClient() - 20, ttos(1.0 / m_dAvFrameTime));
  }*/

  if (m_bShowCellSpaceInfo)
  {
    m_pCellSpace->RenderCells();
  }

}

/*


case IDR_PARTITIONING:
 {
   for (unsigned int i=0; i<m_Vehicles.size(); ++i)
   {
     m_Vehicles[i]->Steering()->ToggleSpacePartitioningOnOff();
   }

   //if toggled on, empty the cell space and then re-add all the
   //vehicles
   if (m_Vehicles[0]->Steering()->isSpacePartitioningOn())
   {
     m_pCellSpace->EmptyCells();

     for (unsigned int i=0; i<m_Vehicles.size(); ++i)
     {
       m_pCellSpace->AddEntity(m_Vehicles[i]);
     }

     ChangeMenuState(hwnd, IDR_PARTITIONING, MFS_CHECKED);
   }
   else
   {
     ChangeMenuState(hwnd, IDR_PARTITIONING, MFS_UNCHECKED);
     ChangeMenuState(hwnd, IDM_PARTITION_VIEW_NEIGHBORS, MFS_UNCHECKED);
     m_bShowCellSpaceInfo = false;

   }
 }

 break;

case IDM_PARTITION_VIEW_NEIGHBORS:
 {
   m_bShowCellSpaceInfo = !m_bShowCellSpaceInfo;

   if (m_bShowCellSpaceInfo)
   {
     ChangeMenuState(hwnd, IDM_PARTITION_VIEW_NEIGHBORS, MFS_CHECKED);

     if (!m_Vehicles[0]->Steering()->isSpacePartitioningOn())
     {
       SendMessage(hwnd, WM_COMMAND, IDR_PARTITIONING, NULL);
     }
   }
   else
   {
     ChangeMenuState(hwnd, IDM_PARTITION_VIEW_NEIGHBORS, MFS_UNCHECKED);
   }
 }
 break;
*/

