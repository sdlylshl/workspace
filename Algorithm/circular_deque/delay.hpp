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
// ���¼���������Ӧ�������������Ӧ������100����,
// ��ϵͳ˯��һ��, Ȼ��ִ������, ������10����,
// ��CPU�ȴ�, Ȼ����ϵͳȥ�л�����������2΢�
void delay(size_t ns)
{
#if defined(__GNUC__) && defined(i386)         // ����Ϊ����, gcc������
  size_t clk, now;
  asm volatile("rdtsc":"=a"(clk)::"edx");
  do
  {
    asm volatile("rep;nop":::"memory");
    asm volatile("rdtsc":"=a"(now)::"edx");
  }while(now - clk < ns);
//#elif defined(_WIN32) || defined(WIN32)        // ����Ϊ����, Win32ϵ�е�ϵͳ
//  Sleep(DWORD(ns / 1000000));
#elif defined (LINUX) || defined (__FreeBSD__) // ����Ϊ����, Linux��FreeBSD Unix
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
