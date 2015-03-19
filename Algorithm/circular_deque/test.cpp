#include <iostream>
#include <cstddef>
#include <cstdlib>

#include "delay.hpp"
#include "timer.hpp"

#include "circular_deque.hpp"
#include "circular_deque_traditional.hpp"
#include <boost/random.hpp>
#include <boost/circular_buffer.hpp>

int main()
{
	typedef std::size_t size_type;
	// 测试数据量SZ, 循环次数LOOPS
  const size_type SZ = 10000000, LOOPS = 5;
  // CPU等待时间DT纳秒
  const size_type DT = 1000000000;
  double rt1 = 0.0, rt2 = 0.0, rt3 = 0.0, rt4 = 0.0;
  std::cout << SZ << " random numbers.\n";
	boost::mt19937 rand;
  timer t;

  // 测试LOOPS次产生SZ个随机数耗费的时间
  delay(DT);
  t.start();
  for(size_type j = 0; j < LOOPS; ++j)
    for(size_type i = 0; i < SZ; ++i)
      rand();
  t.stop();
  rt1 = t;
  std::cout << "random used: " << rt1 / LOOPS << "ms\n";

  // 测试circular_deque的成员函数push_xx和pop_xx的速度
  delay(DT);
  t.start();
  for(unsigned j = 0; j < LOOPS; ++j)
  {
    circular_deque<size_type> cd(SZ);
		while(!cd.full())
      cd.push_front(rand());
		while(!cd.empty())
      cd.pop_front();
  }
  t.stop();
  rt2 = t - rt1;
  std::cout << "circular_deque used: " << rt2 / LOOPS << "ms\n";

  // 测试circular_buffer的成员函数push_xx和pop_xx的速度
  delay(DT);
  t.start();
  for(size_type j = 0; j < LOOPS; ++j)
  {
    boost::circular_buffer<size_type> cb(SZ);
    while(!cb.full())
      cb.push_front(rand());
    while(!cb.empty())
      cb.pop_front();
  }
  t.stop();
  rt3 = t - rt1;
  std::cout << "boost::circular_buffer used: " << rt3 / LOOPS << "ms\n";

  // 测试circular_deque_traditional的成员函数push_xx和pop_xx的速度
  delay(DT);
  t.start();
  for(size_type j = 0; j < LOOPS; ++j)
  {
    circular_deque_traditional<size_type> cdt(SZ);
    while(!cdt.full())
      cdt.push_front(rand());
    while(!cdt.empty())
      cdt.pop_front();
  }
  t.stop();
  rt4 = t - rt1;
  std::cout << "traditional circular deque used: " << rt4 / LOOPS << "ms\n";

  // 测试计时器timer的误差
  delay(DT);
  t.start();
  t.stop();
  std::cout << "tolerance of timer: " << t <<" ms\n";

  std::system("PAUSE");
  return 0;
}
