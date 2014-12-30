// delay.hpp
#ifndef DELAY_HPP_
#define DELAY_HPP_

#if defined(__GNUC__) && defined(i386)
#include <stddef.h>
//#elif defined(WIN32) || defined(_WIN32)
//#include <windows.h>
#else
#include <time.h>
#endif
// 按下键盘立即响应或点击鼠标立即响应误差低于100毫秒,
// 让系统睡眠一会, 然后执行任务, 误差不超过10毫秒,
// 让CPU等待, 然后让系统去切换任务误差不超过2微妙。
void delay(size_t ns)
{
#if defined(__GNUC__) && defined(i386)         // 精度为纳秒, gcc编译器
  size_t clk, now;
  asm volatile("rdtsc":"=a"(clk)::"edx");
  do
  {
    asm volatile("rep;nop":::"memory");
    asm volatile("rdtsc":"=a"(now)::"edx");
  }while(now - clk < ns);
//#elif defined(_WIN32) || defined(WIN32)        // 精度为毫秒, Win32系列的系统
//  Sleep(DWORD(ns / 1000000));
#elif defined (LINUX) || defined (__FreeBSD__) // 精度为纳秒, Linux或FreeBSD Unix
  struct timespec req = {0, ns};
  struct timespec rem, * a = &req, * b = &rem;
  while(clock_nanosleep(CLOCK_REALTIME, 0, a, b) && EINTR = errno)
  {
    struct timespec* tmp = a;
    a = b;
    b = tmp;
  }
#else
  for(long long i = 0, ns *= 1000000; i < ns; ++i) {}
#endif
}

#endif // DELAY_HPP_
