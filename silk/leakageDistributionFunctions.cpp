#ifndef __LEAKAGE_DISTRIBUTION_FUNCTIONS_CPP__
#define __LEAKAGE_DISTRIBUTION_FUNCTIONS_CPP__

#include "leakageDistributionFunctions.hpp"

// list of standard leakage distribution funcitons

double sinMul(double leakage, double time){
	return leakage*sin(time);
}


#endif //__LEAKAGE_DISTRIBUTION_FUNCTIONS_CPP__