#include "ParamLoader.h"

ParamLoader* ParamLoader::Instance()
{
  static ParamLoader instance;
  return &instance;
}

void ParamLoader::recalibrate()
{
    m_MaxSteeringForce = m_SteeringForce * m_SteeringForceTweaker;
    m_SeparationWeight = m_SeparationWeight * m_SteeringForceTweaker;
    m_AlignmentWeight  = m_AlignmentWeight * m_SteeringForceTweaker;
    m_CohesionWeight = m_CohesionWeight * m_SteeringForceTweaker;
    m_ObstacleAvoidanceWeight = m_ObstacleAvoidanceWeight * m_SteeringForceTweaker;
    m_WallAvoidanceWeight  = m_WallAvoidanceWeight * m_SteeringForceTweaker;
    m_WanderWeight = m_WanderWeight * m_SteeringForceTweaker;
    m_SeekWeight  = m_SeekWeight * m_SteeringForceTweaker;
    m_FleeWeight = m_FleeWeight * m_SteeringForceTweaker;
    m_ArriveWeight = m_ArriveWeight * m_SteeringForceTweaker;
    m_PursuitWeight  = m_PursuitWeight * m_SteeringForceTweaker;
    m_OffsetPursuitWeight = m_OffsetPursuitWeight *m_SteeringForceTweaker;
    m_InterposeWeight  = m_InterposeWeight * m_SteeringForceTweaker;
    m_HideWeight = m_HideWeight * m_SteeringForceTweaker;
    m_EvadeWeight = m_EvadeWeight * m_SteeringForceTweaker;
    m_FollowPathWeight  = m_FollowPathWeight * m_SteeringForceTweaker;
}
