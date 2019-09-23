#ifndef CLAMP_HPP
#define CLAMP_HPP

#include <cassert>

template<class T>
constexpr const T &clamp (const T &val, const T &low, const T &high) {
	assert (!(high < low)); //tests whether high < low, aborts the function if true
	return (val < low) ? low : high < val ? high : val;
}

#endif
