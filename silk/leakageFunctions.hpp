#ifndef __LEAKAGE_FUNCTIONS_HPP__
#define __LEAKAGE_FUNCTIONS_HPP__

#define _USE_MATH_DEFINES // for the definition of pi as "M_PI"
#include <cmath>
#include "util_func.hpp"
// list of standard leakage functions

template <typename DataType>
double hammingWeightOut(DataType oldValue, DataType newValue);

template <typename DataType>
double hammingWeightIn(DataType oldValue, DataType newValue);

template <typename DataType>
double hammingDistance(DataType oldValue, DataType newValue);


#endif //__LEAKAGE_FUNCTIONS_HPP__
