#ifndef TIMING_H
#define TIMING_H

#include <sys/time.h>
#include <ctime>

namespace timing
{

static long getTime()
{
  struct timeval tv;
  gettimeofday( &tv, NULL );
  long ret = tv.tv_usec;
  ret /= 1000;
  ret += (tv.tv_sec * 1000);
  return ret;
}

} //namespace timing

#endif // TIMING_H
