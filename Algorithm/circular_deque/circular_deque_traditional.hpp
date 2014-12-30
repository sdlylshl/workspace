// circular_deque_traditional.hpp
#ifndef CIRCULAR_DEQUE_TRADITIONAL_HPP_
#define CIRCULAR_DEQUE_TRADITIONAL_HPP_

#include <cstddef>
#include "compare.hpp"

template <typename T>
class circular_deque_traditional
{
public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  circular_deque_traditional(size_type buf_sz = 0)
  : cap(buf_sz + 1), ptr(new T[cap]), first(cap >> 1), last(first) {}

  circular_deque_traditional(const circular_deque_traditional& cd)
  : cap(cd.cap), ptr(new T[cap]), first(cd.first), last(cd.last)
  {
  	for(difference_type i = first; i != last; ptr[i] = cd.ptr[i])
  	  i = next(i);
	}

  ~circular_deque_traditional() { delete [] ptr; }

  circular_deque_traditional& operator = (const circular_deque_traditional& cd)
  {
  	if(&cd != this)
  	{
	    if(cap < cd.size())
	    {
  	    delete [] ptr;
  	    ptr = new T[cap = cd.cap];
  	    first = cd.first;
  	    last = cd.last;
	    }
	    difference_type j = first;
		  for(difference_type i = cd.first; i != cd.last; i = cd.next(i))
	    {
		    ptr[j] = cd.ptr[i];
		    j = next(j);
	    }
	    last = next(j);
  	}
  	return *this;
  }

  size_type capacity() const { return cap - 1; }
  size_type size() const { return (last - first + cap) % cap; }
  bool empty() const { return first == last; }
  bool full() const { return (last - first + cap) % cap == cap - 1; }
  void clear() { last = first = cap >> 1; }
  void swap(circular_deque_traditional& x)
  {
  	pswap(cap, x.cap);
  	pswap(ptr, x.ptr);
  	pswap(first, x.first);
  	pswap(last, x.last);
  }

  reference operator [](difference_type i) { return ptr[current(i)]; }
  const_reference operator [](difference_type i) const { return ptr[current(i)]; }
  reference at(difference_type i) {	return ptr[current(i)]; }
  const_reference at(difference_type i) const {	return ptr[current(i)]; }

  reference front() { return ptr[first]; }
  const_reference front() const { return ptr[first]; }
  reference back() { return ptr[previous(last)]; }
  const_reference back() const { return ptr[previous(last)]; }

  void push_front(const_reference x)
  {
  	difference_type prev = previous(first);
  	first = prev;
  	ptr[first] = x;
  }

  void push_back(const_reference x)
  {
  	difference_type n = next(last);
  	ptr[last] = x;
  	last = n;
  }

  void pop_back() {	last = previous(last); }
  void pop_front() { first = next(first); }

protected:
  difference_type previous(difference_type i) const { return (i - 1 + cap) % cap; }
  difference_type next(difference_type i) const { return (i + 1 + cap) % cap; }
  difference_type current(difference_type i) const { return (first + i + cap) % cap; }
  template <typename U>
  void pswap(U& x, U& y) { U t = x; x = y, y = t; }
  size_type cap;
  T* ptr;
  difference_type first, last;
};  // circular_deque_traditional


#endif  // CIRCULAR_DEQUE_TRADITIONAL_HPP_
