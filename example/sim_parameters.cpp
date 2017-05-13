#include<iostream>
#include"../silk/silk.hpp"
using namespace std;

void bar(){
	U8 var = 7;
	U8 var1 = 0;
	U8 var2 = 3;
	U8 var3 = 5+ var1;
	U8 var4 = 1;
}
	

int main(){
	
	U8::setLeakageFunction(hammingWeightOut);
	Tracer::setLeakagePointsNbr(10);
	
	Tracer::clearTrace();
	bar();
	Tracer::traceToFile("sim.csv");
	
	Tracer::setLeakageOverlap(2);
	Tracer::clearTrace();
	bar();
	Tracer::traceToFile("sim_overlap.csv");
	
	Tracer::setLeakageOverlap(0);
	Tracer::setLeakageDistributionFunc(sinMul, M_PI);
	Tracer::clearTrace();
	bar();
	Tracer::traceToFile("sim_distr.csv");
	
	Tracer::setLeakageOverlap(2);
	Tracer::clearTrace();
	bar();
	Tracer::traceToFile("sim_distr_overlap.csv");
	
	return 0;
}
