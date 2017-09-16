#include "PrecisionTimer.h"

PrecisionTimer::PrecisionTimer(): m_NormalFPS(0.0),
                  m_SlowFPS(1.0),
                  m_TimeElapsed(0.0),
                  m_bStarted(false),
                  m_LastTimeElapsed(0.0),
                  m_bSmoothUpdates(false)
{

  m_FrameTime.tv_sec = 0.0;
  m_FrameTime.tv_nsec = 0.0;

  m_LastTime.tv_sec = 0.0;
  m_LastTime.tv_nsec = 0.0;

  m_LastTimeInTimeElapsed.tv_sec = 0.0;
  m_LastTimeInTimeElapsed.tv_nsec = 0.0;

  m_PerfCountFreq.tv_nsec = 0.0;

  m_StartTime.tv_sec = 0.0;
  m_StartTime.tv_nsec = 0.0;

  clock_getres( CLOCK_REALTIME, &m_PerfCountFreq);

  m_TimeScale = NANO/(double)m_PerfCountFreq.tv_nsec;
}

PrecisionTimer::PrecisionTimer(double fps): m_NormalFPS(fps),
                  m_SlowFPS(1.0),
                  m_TimeElapsed(0.0),
                  m_bStarted(false),
                  m_LastTimeElapsed(0.0),
                  m_bSmoothUpdates(false)
{
    m_FrameTime.tv_sec = 0.0;
    m_FrameTime.tv_nsec = 0.0;

    m_LastTime.tv_sec = 0.0;
    m_LastTime.tv_nsec = 0.0;

    m_LastTimeInTimeElapsed.tv_sec = 0.0;
    m_LastTimeInTimeElapsed.tv_nsec = 0.0;

    m_PerfCountFreq.tv_nsec = 0.0;

    m_StartTime.tv_sec = 0.0;
    m_StartTime.tv_nsec = 0.0;

  //how many ticks per nsec do we get
  clock_getres( CLOCK_REALTIME, &m_PerfCountFreq);

  m_TimeScale = NANO/m_PerfCountFreq.tv_nsec;

  //calculate nsecs per frame
  m_FrameTime.tv_nsec = (1.0/NANO)*(m_PerfCountFreq.tv_nsec / m_NormalFPS);
}

void PrecisionTimer::Start()
{
  m_bStarted = true;

  m_TimeElapsed = 0.0;

  //get the time
  clock_gettime( CLOCK_REALTIME,  &m_LastTime);

  //keep a record of when the timer was started
  m_StartTime = m_LastTimeInTimeElapsed = m_LastTime;

  //update time to render next frame
  double nextTime = time(m_LastTime) + time(m_FrameTime);
  double integerPart;
  m_NextTime.tv_nsec = (1.0/m_TimeScale)*modf(nextTime, &integerPart);
  m_NextTime.tv_sec = (int)integerPart;

  return;
}
