// compare.hpp
#ifndef COMPARE_HPP_
#define COMPARE_HPP_

template <typename T>
inline bool operator !=(const T& x, const T& y) { return !(x == y); }

template <typename T>
inline bool operator <=(const T& x, const T& y) { return !(y < x); }

template <typename T>
inline bool operator >(const T& x, const T& y) { return y < x; }

template <typename T>
inline bool operator >=(const T& x, const T& y) { return !(x < y); }

#endif // COMPARE_HPP_
