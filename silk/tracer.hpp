#ifndef __TRACER_HPP__
#define __TRACER_HPP__

#include<vector>
#include<stdint.h>
#include<iostream> //std output
#include<fstream> //files
#include<random> //normal distribution
#include<cmath> // sqrt

class Tracer{
protected:
	static std::vector<double> _trace;
	static unsigned _leakagePointsNbr;
	static double (*_leakageDistributionFunc)(double, double);
	static double _leakageInterval;
	static unsigned _leakageOverlap;
	static double _noiseVariance;
	static std::default_random_engine _randomGenerator;
	
	static void saveVector(const char* filename, const std::vector<double> &vec);
public:
	Tracer();
	~Tracer();
	
	static void clearTrace();
	
	static std::vector<double> getTrace();
	static std::vector<double> getNoisyTrace();
	static void traceToFile(const char* filename);
	static void noisyTraceToFile(const char* filename);
	
	static void setLeakageInterval(unsigned interval);
	static void setLeakagePointsNbr(unsigned pts_nbr);
	static void setLeakageDistributionFunc(double (*_leakageDistributionFunc)(double, double), double pts_nbr=1);
	static void setLeakageOverlap(unsigned overlap);
	static void setNoiseVariance(double var); // set signal to noise ratio
	static void setRandomSeed(unsigned seed);
};

#endif //__TRACER_HPP__
