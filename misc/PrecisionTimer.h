#ifndef PRECISIONTIMER_H_
#define PRECISIONTIMER_H_

#include <cassert>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const double NANO = 0.000000001;

class PrecisionTimer
{

private:

  struct timespec  	m_CurrentTime,
                    m_LastTime,
                    m_LastTimeInTimeElapsed,
                    m_NextTime,
                    m_StartTime,
                    m_FrameTime,
                    m_PerfCountFreq;

  double    		m_TimeElapsed,
                    m_LastTimeElapsed,
                    m_TimeScale;

  double    		m_NormalFPS;
  double    		m_SlowFPS;

  bool      		m_bStarted;


  bool      		m_bSmoothUpdates;

public:

  PrecisionTimer();
  PrecisionTimer(double fps);

  void    Start();

  inline bool    ReadyForNextFrame();

  //only use this after a call to the above.
  //double  GetTimeElapsed(){return m_TimeElapsed;}

  inline double  TimeElapsed();

  inline double time(const struct timespec& timespc);


  double  CurrentTime()
  {
    clock_gettime( CLOCK_REALTIME, &m_CurrentTime);

    return (time(m_CurrentTime) - time(m_StartTime));
  }

  bool    Started()const{return m_bStarted;}

  void    SmoothUpdatesOn(){m_bSmoothUpdates = true;}
  void    SmoothUpdatesOff(){m_bSmoothUpdates = false;}

};

inline double PrecisionTimer::time(const struct timespec& timespc)
{
    return timespc.tv_sec + timespc.tv_nsec*m_TimeScale;
}

inline bool PrecisionTimer::ReadyForNextFrame()
{
  assert(m_NormalFPS && "PrecisionTimer::ReadyForNextFrame<No FPS set in timer>");

  clock_gettime( CLOCK_REALTIME, &m_CurrentTime );

  if (time(m_CurrentTime) > time(m_NextTime))
  {

    m_TimeElapsed = time(m_CurrentTime) - time(m_LastTime);
    m_LastTime    = m_CurrentTime;

    //update time to render next frame
    double nextTime = time(m_CurrentTime) + time(m_FrameTime);
    double integerPart;

    m_NextTime.tv_nsec = (1.0/m_TimeScale)*modf(nextTime, &integerPart);
    m_NextTime.tv_sec = (int)integerPart;

    return true;
  }

  return false;
}

inline double PrecisionTimer::TimeElapsed()
{
  m_LastTimeElapsed = m_TimeElapsed;

  clock_gettime( CLOCK_REALTIME, &m_CurrentTime);

  m_TimeElapsed = time(m_CurrentTime) - time(m_LastTimeInTimeElapsed);

  m_LastTimeInTimeElapsed    = m_CurrentTime;

  const double Smoothness = 5.0;

  if (m_bSmoothUpdates)
  {
    if (m_TimeElapsed < (m_LastTimeElapsed * Smoothness))
    {
      return m_TimeElapsed;
    }

    else
    {
      return 0.0;
    }
  }

  else
  {
    return m_TimeElapsed;
  }

}


#endif /* PRECISIONTIMER_H_ */
