#ifndef __LEAKAGE_FUNCTIONS_CPP__
#define __LEAKAGE_FUNCTIONS_CPP__

#include "leakageFunctions.hpp"

// list of standard leakage funcitons

template <typename DataType>
double hammingWeightOut(DataType oldValue, DataType newValue){
	return double(0*oldValue + HW(newValue)+1);  // +1 in order to avoid 0 (and multiplication by 0)
}

template <typename DataType>
double hammingWeightIn(DataType oldValue, DataType newValue){
	return double(HW(oldValue) + 0*newValue+1);  // +1 in order to avoid 0 (and multiplication by 0)
}

template <typename DataType>
double hammingDistance(DataType oldValue, DataType newValue){
	return double(HD(oldValue, newValue)+1);  // +1 in order to avoid 0 (and multiplication by 0)
}

#endif //__LEAKAGE_FUNCTIONS_CPP__
