#ifndef PARAMLOADER_H
#define PARAMLOADER_H
//-----------------------------------------------------------------------------
//
//  Name:   ParamLoader.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to parse a parameter file for the steering behavior project
//-----------------------------------------------------------------------------
#include "constants.h"
#include "misc/iniFileLoaderBase.h"
#include "misc/utils.h"



#define Prm (*ParamLoader::Instance())


class ParamLoader
{
private:

    ParamLoader()
  {
        m_NumAgents               = 300;
        m_NumObstacles            = 7;
        m_MinObstacleRadius       = 10.0;
        m_MaxObstacleRadius       = 30.0;

        m_NumCellsX               = 7;
        m_NumCellsY               = 7;

        m_NumSamplesForSmoothing  = 10;

        m_SteeringForceTweaker    = 200;
        m_SteeringForce           = 2.0;
        m_MaxSpeed                = 150.0;
        m_VehicleMass             = 1.0;
        m_VehicleScale            = 3.0;

        m_SeparationWeight        = 1.0;
        m_AlignmentWeight         = 1.0;
        m_CohesionWeight          = 2.0;
        m_ObstacleAvoidanceWeight = 10.0;
        m_WallAvoidanceWeight     = 10.0;
        m_WanderWeight            = 1.0;
        m_SeekWeight              = 1.0;
        m_FleeWeight              = 1.0;
        m_ArriveWeight            = 1.0;
        m_PursuitWeight           = 10;
        m_OffsetPursuitWeight     = 1.0;
        m_InterposeWeight         = 1.0;
        m_HideWeight              = 1.0;
        m_EvadeWeight             = 0.01;
        m_FollowPathWeight        = 0.05;

        m_ViewDistance            = 50.0;
        m_MinDetectionBoxLength   = 40.0;
        m_WallDetectionFeelerLength=40.0;

        m_prWallAvoidance         = 0.5;
        m_prObstacleAvoidance     = 0.5;
        m_prSeparation            = 0.2;
        m_prAlignment             = 0.3;
        m_prCohesion              = 0.6;
        m_prWander                = 0.8;
        m_prSeek                  = 0.8;
        m_prFlee                  = 0.6;
        m_prEvade                 = 1.0;
        m_prHide                  = 0.8;
        m_prArrive                = 0.5;

        m_seek                    = false;
        m_flee                    = false;
        m_arrive                  = false;
        m_wander                  = true;
        m_cohesion                = true;
        m_separation              = true;
        m_allignment              = true;
        m_obstacle_avoidance      = false;
        m_wall_avoidance          = false;
        m_follow_path             = false;
        m_pursuit                 = false;
        m_evade                   = false;
        m_interpose               = false;
        m_hide                    = false;
        m_flocking                = true;
        m_offset_pursuit          = false;
        m_shoal                   = false;

        m_singleagent             = false;
        m_multiagent              = true;


        m_MaxTurnRatePerSecond    = Pi;

        recalibrate();
  }

public:

  static ParamLoader* Instance(); 

private:

  int	 m_NumAgents;
  int	 m_NumObstacles;
  double m_MinObstacleRadius;
  double m_MaxObstacleRadius;

  //number of horizontal cells used for spatial partitioning
  int   m_NumCellsX;
  //number of vertical cells used for spatial partitioning
  int   m_NumCellsY;

  //how many samples the smoother will use to average a value
  int   m_NumSamplesForSmoothing;

  //used to tweak the combined steering force (simply altering the MaxSteeringForce
  //will NOT work!This tweaker affects all the steering force multipliers
  //too).
  double m_SteeringForceTweaker;
  double m_SteeringForce;

  double m_MaxSteeringForce;
  double m_MaxSpeed;
  double m_VehicleMass;

  double m_VehicleScale;
  double m_MaxTurnRatePerSecond;

  double m_SeparationWeight;
  double m_AlignmentWeight ;
  double m_CohesionWeight  ;
  double m_ObstacleAvoidanceWeight;
  double m_WallAvoidanceWeight;
  double m_WanderWeight    ;
  double m_SeekWeight      ;
  double m_FleeWeight      ;
  double m_ArriveWeight    ;
  double m_PursuitWeight   ;
  double m_OffsetPursuitWeight;
  double m_InterposeWeight ;
  double m_HideWeight      ;
  double m_EvadeWeight     ;
  double m_FollowPathWeight;

  //how close a neighbour must be before an agent perceives it (considers it
  //to be within its neighborhood)
  double m_ViewDistance;

  //used in obstacle avoidance
  double m_MinDetectionBoxLength;

  //used in wall avoidance
  double m_WallDetectionFeelerLength;

  //these are the probabilities that a steering behavior will be used
  //when the prioritized dither calculate method is used
  double m_prWallAvoidance;
  double m_prObstacleAvoidance;
  double m_prSeparation;
  double m_prAlignment;
  double m_prCohesion;
  double m_prWander;
  double m_prSeek;
  double m_prFlee;
  double m_prEvade;
  double m_prHide;
  double m_prArrive;

private:
  bool m_seek;
  bool m_flee;
  bool m_arrive;
  bool m_wander;
  bool m_cohesion;
  bool m_separation;
  bool m_allignment;
  bool m_obstacle_avoidance;
  bool m_wall_avoidance;
  bool m_follow_path;
  bool m_pursuit;
  bool m_evade;
  bool m_interpose;
  bool m_hide;
  bool m_flocking;
  bool m_offset_pursuit;
  bool m_shoal;

  bool m_singleagent;
  bool m_multiagent;

private:
  void recalibrate();

public:

  int	 NumAgents(){return m_NumAgents;}
  int	 NumObstacles(){return m_NumObstacles;}
  double MinObstacleRadius(){return m_MinObstacleRadius;}
  double MaxObstacleRadius(){return m_MaxObstacleRadius;}

  //number of horizontal cells used for spatial partitioning
  int   NumCellsX(){return m_NumCellsX;}
  //number of vertical cells used for spatial partitioning
  int   NumCellsY(){return m_NumCellsY;}

  //how many samples the smoother will use to average a value
  int   NumSamplesForSmoothing(){return m_NumSamplesForSmoothing;}

  //used to tweak the combined steering force (simply altering the MaxSteeringForce
  //will NOT work!This tweaker affects all the steering force multipliers
  //too).
  double SteeringForceTweaker(){return m_SteeringForceTweaker;}
  double SteeringForce(){return m_SteeringForce;}

  double MaxSteeringForce(){return m_MaxSteeringForce;}
  double MaxSpeed(){return m_MaxSpeed;}
  double VehicleMass(){return m_VehicleMass;}

  double VehicleScale(){ return m_VehicleScale;}
  double MaxTurnRatePerSecond(){return m_MaxTurnRatePerSecond;}

  double SeparationWeight(){return m_SeparationWeight;}
  double AlignmentWeight(){return m_AlignmentWeight;}
  double CohesionWeight(){return m_CohesionWeight;}
  double ObstacleAvoidanceWeight(){return m_ObstacleAvoidanceWeight;}
  double WallAvoidanceWeight(){return m_WallAvoidanceWeight;}
  double WanderWeight(){return m_WanderWeight;}
  double SeekWeight(){return m_SeekWeight;}
  double FleeWeight(){return m_FleeWeight;}
  double ArriveWeight(){return m_ArriveWeight;}
  double PursuitWeight(){return m_PursuitWeight;}
  double OffsetPursuitWeight(){return m_OffsetPursuitWeight;}
  double InterposeWeight(){return m_InterposeWeight;}
  double HideWeight(){return m_HideWeight;}
  double EvadeWeight(){return m_EvadeWeight;}
  double FollowPathWeight(){return m_FollowPathWeight;}

  //how close a neighbour must be before an agent perceives it (considers it
  //to be within its neighborhood)
  double ViewDistance(){return m_ViewDistance;}

  //used in obstacle avoidance
  double MinDetectionBoxLength(){return m_MinDetectionBoxLength;}

  //used in wall avoidance
  double WallDetectionFeelerLength(){return m_WallDetectionFeelerLength;}

  //these are the probabilities that a steering behavior will be used
  //when the prioritized dither calculate method is used
  double prWallAvoidance(){return m_prWallAvoidance;}
  double prObstacleAvoidance(){return m_prObstacleAvoidance;}
  double prSeparation(){return m_prSeparation;}
  double prAlignment(){return m_prAlignment;}
  double prCohesion(){return m_prCohesion;}
  double prWander(){return m_prWander;}
  double prSeek(){return m_prSeek;}
  double prFlee(){return m_prFlee;}
  double prEvade(){return m_prEvade;}
  double prHide(){return m_prHide;}
  double prArrive(){return m_prArrive;}

  void setNumAgents(int n){m_NumAgents=n;}
  void setNumObstacles(int n){m_NumObstacles=n;}
  void setMinObstacleRadius(double n){m_MinObstacleRadius=n;}
  void setMaxObstacleRadius(double n){m_MaxObstacleRadius=n;}
  void setNumCellsX(int n) {m_NumCellsX=n;}
  void setNumCellsY(int n) {m_NumCellsY=n;}
  void setNumSamplesForSmoothing(int n){m_NumSamplesForSmoothing=n;}

  void setSteeringForceTweaker(double n){m_SteeringForceTweaker=n; recalibrate();}
  void setSteeringForce(double n){m_SteeringForce=n;}
  void setMaxSpeed(double n){m_MaxSpeed=n;}
  void setVehicleMass(double n){m_VehicleMass=n;}
  void setVehicleScale(double n){m_VehicleScale=n;}

  void toggleSeek(){m_seek=!m_seek;}
  void toggleFlee(){m_flee=!m_flee;}
  void toggleArrive(){m_arrive=!m_arrive;}
  void toggleWander(){if(!m_flocking){m_wander=!m_wander;} else return;}
  void toggleCohesion(){if(!m_flocking){m_cohesion=!m_cohesion;} else return;}
  void toggleSeparation(){if(!m_flocking){m_separation=!m_separation;} else return;}
  void toggleAllignment(){if(!m_flocking){m_allignment=!m_allignment;} else return;}
  void toggleObstacleAvoidance(){m_obstacle_avoidance=!m_obstacle_avoidance;}
  void toggleWallAvoidance(){m_wall_avoidance=!m_wall_avoidance;}
  void toggleFollowPath(){m_follow_path=!m_follow_path;}
  void togglePursuit(){m_pursuit=!m_pursuit;}
  void toggleEvade(){m_evade=!m_evade;}
  void toggleInterpose(){m_interpose=!m_interpose;}
  void toggleHide(){m_hide=!m_hide;}
  void toggleFlocking(){m_flocking=!m_flocking; m_wander=!m_wander; m_cohesion=!m_cohesion; m_separation=!m_separation; m_allignment=!m_allignment;}
  void toggleOffsetPursuit(){m_offset_pursuit=!m_offset_pursuit;}
  void toggleShoal(){m_shoal=!m_shoal;}
  bool seek(){return m_seek;}
  bool flee(){return m_flee;}
  bool arrive(){return m_arrive;}
  bool wander(){return m_wander;}
  bool cohesion(){return m_cohesion;}
  bool separation(){return m_separation;}
  bool allignment(){return m_allignment;}
  bool obstacle_avoidance(){return m_obstacle_avoidance;}
  bool wall_avoidance(){return m_wall_avoidance;}
  bool follow_path(){return m_follow_path;}
  bool pursuit(){return m_pursuit;}
  bool evade(){return m_evade;}
  bool interpose(){return m_interpose;}
  bool hide(){return m_hide;}
  bool flocking(){return m_flocking;}
  bool offset_pursuit(){return m_offset_pursuit;}
  bool shoal(){return m_shoal;}

  bool singleagent(){return m_singleagent;}
  bool multiagent(){return m_multiagent;}

  void toggleAgentMode(){m_singleagent=!m_singleagent; m_multiagent=!m_multiagent;}
};






#endif
