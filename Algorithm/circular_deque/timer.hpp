#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <iostream>

#if (defined WIN32) || (defined _WIN32)
#include <windows.h>

class timer
{
public:
  timer() {}
  void start() { QueryPerformanceCounter(&begin); }
  void stop() { QueryPerformanceCounter(&end); }

  double duration() const
  {
	  return (end.QuadPart - begin.QuadPart) * 1000.0 / frequency();
  }
  operator double() const { return duration(); }
  friend std::ostream& operator << (std::ostream& os, const timer& t)
  {
  	os << t.duration();
  	return os;
  }
private:
  LARGE_INTEGER begin, end;
  static LARGE_INTEGER fr;
  static double frequency()
  {
  	QueryPerformanceFrequency(&fr);
  	return double(fr.QuadPart);
  }
};

LARGE_INTEGER timer::fr;

#elif defined(__FreeBSD__) || defined(LINUX)
#include <time.h>

class timer
{
public:
  timer() {}
  void start() { clock_gettime(CLOCK_MONOTONIC, &begin); }
  void stop() { clock_gettime(CLOCK_MONOTONIC, &end); }

  double duration() const
  {
  	struct timespec ts;
  	ts.tv_sec = end.tv_sec - begin.tv_sec;
  	ts.tv_nsec = end.tv_nsec - begin.tv_nsec;
  	return ts.tv_sec * 1000.0 + ts.tv_nsec / 1000000.0;
  }
  operator double() const { return duration(); }
  friend std::ostream& operator << (std::ostream& os, const timer& t)
  {
  	os << t.duration();
  	return os;
  }
private:
  struct timespec begin, end;
};

#else
#include <ctime>

class timer
{
public:
  timer() {}
  void start() { begin = std::clock(); }
  void stop() { end = std::clock(); }

  double duration() const { return end - begin; }
  operator double() const { return duration(); }
  friend std::ostream& operator << (std::ostream& os, const timer& t)
  {
  	os << t.duration();
  	return os;
  }
private:
  std::clock_t begin, end;
};

#endif

#endif // TIMER_HPP_
