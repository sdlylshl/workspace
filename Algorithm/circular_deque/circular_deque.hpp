// circular_deque.hpp
#ifndef CIRCULAR_DEQUE_HPP_
#define CIRCULAR_DEQUE_HPP_

#include <cstddef>     // std::size_t和std::ptrdiff_t
#include "compare.hpp" // 定义!=, <=, >, >=四个运算符

// 静态循环双端队列, 物理上, 它是一段连续的内存空间,
// 逻辑上, 它是一个环形结构
template <typename T>
class circular_deque
{
public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  circular_deque(size_type buf_sz = 0) : start(new T[buf_sz + 1]),
  finish(start + buf_sz + 1), first(start + ((buf_sz + 1) >> 1)), last(first) {}

  circular_deque(const circular_deque& x) : start(new T[x.finish - x.start]),
  finish(start + (x.finish - x.start)), first(start + (x.first - x.start)),
  last(start + (x.last - x.start))
  {
  	T* f1 = first, * f2 = x.first, * l2 = x.last;
  	for(; f2 != l2; *f1++ = *f2++)
  	{
  	  if(f2 == x.finish)
  	  	f2 = x.start;
  	  if(f1 == finish)
  	  	f1 = start;
  	}
  }

  // 循环队列的析构函数
  ~circular_deque() { delete [] start; }

	// 复制一个队列
  circular_deque& operator = (const circular_deque& x)
  {
  	if(&x != this)
  	{
  		if(capacity() < x.size())
  		{
  		  delete [] start;
  		  size_type cap = x.finish - x.start;
  		  start = new T[cap];
  		  finish = start + cap;
		    first = start + (x.first - x.start);
		  }
  	  T* f1 = first, * f2 = x.first, * l2 = x.last;
  	  for(; f2 != l2; *f1++ = *f2++)
  	  {
  	    if(f2 == x.finish)
  	  	  f2 = x.start;
  	    if(f1 == finish)
  	  	  f1 = start;
  	  }
	    if(f1 == finish)
  	  	f1 = start;
	    last = f1;
  	}
  	return *this;
  }

  // 预留空间,与boost::circular_buffer的成员函数reserve的行为不同,
  // 与std::vector的成员函数reserve的行为类似
  void reserve(size_type new_sz)
  {
  	if(capacity() < new_sz)
  	{
  		size_type buf = new_sz + 1;
  		T* new_start = new T[buf], * new_finish = new_start + buf;
			T* new_last = new_start + (buf >> 1), * new_first = new_last;
			T* f2 = first, * l2 = last;
  	  for(; f2 != l2; *new_last++ = *f2++)
  	  {
  	    if(f2 == finish)
  	  	  f2 = start;
  	    if(new_last == new_finish)
  	  	  new_last = new_start;
  	  }
	    if(new_last == new_finish)
  	  	new_last = new_start;
	    start = new_start;
	    finish = new_finish;
	    first = new_first;
			last = new_last;
  	}
  }

  // 队列的总容量, 即最多能容纳的元素个数
  size_type capacity() const { return finish - start - 1; }

  // 队列中当前存储的元素个数
  size_type size() const
  {
  	size_type cap = finish - start;
  	return (last - first + cap) % cap;
  }

	// 判断队列是否空
  bool empty() const { return first == last; }

  // 判断队列是否满, 既然ciecular_deque容量固定, 就应该有此成员函数
  bool full() const
  {
  	T* tlast = (last == finish ? start : last);
  	return tlast + 1 == first;
  }

  // 清空队列中所有元素, 并不真正销毁每个元素, 仅仅移动指针罢了
  void clear() { last = first = (start + ((finish - start) >> 1)); }

  // 交换两个队列, 仅仅交换指针就可以了
  void swap(circular_deque& x)
  {
  	pswap(start, x.start);
  	pswap(finish, x.finish);
  	pswap(first, x.first);
  	pswap(last, x.last);
  }
  // 允许用下标访问任何一个元素
  reference operator [](difference_type i)
  {
  	difference_type idx = first - start + i, cap = finish - start;
  	if(idx >= cap)
  	  idx -= cap;
  	return *(start + idx);
  }

  const_reference operator [](difference_type i) const
  {
  	difference_type idx = first - start + i, cap = finish - start;
  	if(idx >= cap)
  	  idx -= cap;
  	return *(start + idx);
  }

  // 引用队头元素, 如果队列空, 结果无法预料
  reference front()
  {
  	if(first == finish)
  	  return *start;
  	return *first;
  }

  const_reference front() const
  {
  	if(first == finish)
  	  return *start;
  	return *first;
  }

  // 引用队尾元素, 如果队列空, 结果无法预料
  reference back()
  {
  	if(last == start)
  	  return *(finish - 1);
  	return *(last - 1);
  }

  const_reference back() const
  {
  	if(last == start)
  	  return *(finish - 1);
  	return *(last - 1);
  }

  // 把一个元素插入到队头前, 成为新队头
  void push_front(const_reference x)
  {
  	if(first == start)
  	  first = finish;
  	*--first = x;
  }

  // 把一个元素插入到队尾后, 成为新队尾
  void push_back(const_reference x)
  {
  	if(last == finish)
  	  last = start;
  	*last++ = x;
  }

  // 删除队头元素, 如果队列空, 将引起指针混乱
  void pop_front()
  {
  	if(first == finish)
  	  first = start;
  	++first;
  }

  // 删除队尾元素, 如果队列空, 将引起指针混乱
  void pop_back()
  {
  	if(last == start)
  	  last = finish;
  	--last;
  }

  // ... 有待添加更多公有成员函数, 该工作留给您吧
protected:
	T* start, * finish, * first, * last;

	template <typename U>
  void pswap(U& x, U& y) { U t = x;  x = y, y = t; }

  // 交换两个队列
	friend void swap(circular_deque& x, circular_deque& y) { x.swap(y); }

  // 判断两个队列是否相等
	friend bool operator ==(const circular_deque& x, const circular_deque& y)
	{
		const T* f1 = x.first, * l1 = x.last, * f2 = y.first, * l2 = y.last;
		if(l1 == x.start)
		  l1 = x.finish - 1;
		if(l2 == y.start)
		  l2 = y.finish - 1;
		for(; f1 != l1 && f2 != l2 && *f1 == *f2; ++f1, ++f2)
		{
		  if(f1 == x.finish)
		    f1 = x.start;
		  if(f2 == y.finish)
		    f2 = y.start;
		}
		return f1 == l1 && f2 == l2;
	}

  // 比较两个队列大小
	friend bool operator <(const circular_deque& x, const circular_deque& y)
	{
		const T* f1 = x.first, * l1 = x.last, * f2 = y.first, * l2 = y.last;
		if(l1 == x.start)
		  l1 = x.finish - 1;
		if(l2 == y.start)
		  l2 = y.finish - 1;
		for(; f1 != l1 && f2 != l2 && *f1 == *f2; ++f1, ++f2)
		{
		  if(f1 == x.finish)
		    f1 = x.start;
		  if(f2 == y.finish)
		    f2 = y.start;
		}
		return (f1 == l1 && f2 != l2) || (f1 != l1 && f2 != l2 && *f1 < *f2);
	}
};  // circular_deque

#endif  // CIRCULAR_DEQUE_HPP_
