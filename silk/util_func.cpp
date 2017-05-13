#ifndef __UTIL_FUNC_CPP__
#define __UTIL_FUNC_CPP__

#include "util_func.hpp"

// ---- util funcitons ----

// Hamming Weight
unsigned HW(unsigned value){
	unsigned result = 0;
	while (value != 0){
		if (value % 2 == 1){
			result+=1.0;
		}
		value/=2;
	}
	return result;
}

//hamming distance
unsigned HD(unsigned value1, unsigned value2){
	return HW(value1^value2);
}

#endif //__UTIL_FUNC_CPP__
