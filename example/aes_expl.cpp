/*
this is a simple example of main
funciton that generates simulations for AES code
*/
#include <iostream>

#include "aes.hpp"

using namespace std;

int main(){	

	U8 key [Nrows][Ncols];
	U8 state [Nrows][Ncols];
		
	//test vector key : 2b7e1516 28aed2a6 abf71588 09cf4f3c
	key[0][0] = 0x2B;	key[0][1] = 0x28;	key[0][2] = 0xAB;	key[0][3] = 0x09;
	key[1][0] = 0x7E;	key[1][1] = 0xAE;	key[1][2] = 0xF7;	key[1][3] = 0xCF;
	key[2][0] = 0x15;	key[2][1] = 0xD2;	key[2][2] = 0x15;	key[2][3] = 0x4F;
	key[3][0] = 0x16;	key[3][1] = 0xA6;	key[3][2] = 0x88;	key[3][3] = 0x3c;
	
	//test vector state : 6bc1bee2 2e409f96 e93d7e11 7393172a
	state[0][0] = 0x6B;	state[0][1] = 0x2e;	state[0][2] = 0xe9;	state[0][3] = 0x73;
	state[1][0] = 0xC1;	state[1][1] = 0x40;	state[1][2] = 0x3d;	state[1][3] = 0x93;	
	state[2][0] = 0xBE;	state[2][1] = 0x9f;	state[2][2] = 0x7e;	state[2][3] = 0x17;
	state[3][0] = 0xE2;	state[3][1] = 0x96;	state[3][2] = 0x11;	state[3][3] = 0x2a;
	
	//expected result : 3ad77bb4 0d7a3660 a89ecaf3 2466ef97
	
	cout<<"Key\n";
	print(key);
	
	cout<<"Message\n";
	print(state);
	
	
	//setup MemoryUnit
	U8::setLeakageFunction(hammingWeightOut);
	Tracer::setLeakagePointsNbr(10); // 10 leakage points are generated for each operation
	Tracer::setLeakageDistributionFunc(sinMul, M_PI); // leakage distribution function is sinus(x) on the interval [0;3.14]
	Tracer::setLeakageOverlap(2);
	
	Tracer::clearTrace(); //clears the trace (now vector is empty)
	
	cipher(state, key);
	
	Tracer::traceToFile("aesSimulatedTrace.csv");
	
	Tracer::setNoiseVariance(0.1);
	Tracer::noisyTraceToFile("aesSimulatedNoisyTrace0.csv"); // noisy trace
	Tracer::noisyTraceToFile("aesSimulatedNoisyTrace1.csv"); // ANOTHER noisy trace (no need to execute cipher() again)
	
	Tracer::setNoiseVariance(0.05);
	Tracer::noisyTraceToFile("aesSimulatedNoisyTrace3.csv"); // yet another noisy trace with less noise
	
	cout<<"Cipher\n";
	print(state);
	
	return 0;
}
