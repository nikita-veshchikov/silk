/*
this file includes several testes that are mainly used
to check that that the code is not broken (during compilation)
and also to check new features added into the code
*/

#include <iostream>
#include <stdint.h>
#include "../silk/silk.hpp"
using namespace std;

int main(){
	
	U8 vec[3];
	vec[0] = U8(5);
	vec[1] = U8(6);
	vec[2] = U8(7);
	cout<<"vec:"<<short(vec[0].getValue())<<endl;
	
	U8 vec1[] = {0x5,0x10,0x15};
	cout<<"vec1:"<<short(vec1[2].getValue())<<endl;
	
	U8 intVal = 10;
	
	cout<<"assign int:"<<short(intVal.getValue())<<endl;
	
	int vecInt[]={0,1,2};
	U8 idx = 1;
	cout<<"vec index:"<< vecInt[idx]<<endl;
	
	U8 tmp(9);
	U8 tmp1;
	
	cout<<(int)tmp.getValue()<<endl;
	
	tmp = U8(uint8_t(5));
	cout<<(int)tmp.getValue()<<endl;
	
	tmp1 = tmp+tmp;
	cout<<"+:"<<(int)tmp1.getValue()<<endl;
	tmp1 = tmp-tmp;
	cout<<"-:"<<(int)tmp1.getValue()<<endl;
	tmp1 = tmp*tmp;
	cout<<"*:"<<(int)tmp1.getValue()<<endl;
	tmp1 = tmp/tmp;
	cout<<"/:"<<(int)tmp1.getValue()<<endl;
	tmp1 = tmp%tmp;
	cout<<"%:"<<(int)tmp1.getValue()<<endl;
	++tmp1;
	cout<<"prec++:"<<(int)tmp1.getValue()<<endl;
	tmp1++;
	cout<<"post++:"<<(int)tmp1.getValue()<<endl;
	--tmp1;
	cout<<"prec--:"<<(int)tmp1.getValue()<<endl;
	tmp1--;
	cout<<"post--:"<<(int)tmp1.getValue()<<endl;
	
	U8 a(2), b(7);
	tmp = (a&b);
	cout<<"&:"<<short(tmp.getValue())<<endl;
	tmp = (a|b);
	cout<<"|:"<<short(tmp.getValue())<<endl;
	tmp = (a^b);
	cout<<"^:"<<short(tmp.getValue())<<endl;
	tmp = (~b);
	cout<<"~:"<<short(tmp.getValue())<<endl;
	tmp = b<<1;
	cout<<"<<:"<<short(tmp.getValue())<<endl;
	tmp = (b>>1);
	cout<<">>:"<<short(tmp.getValue())<<endl;
	
	cout<<"a>b:"<<(a>b)<<endl;
	cout<<"a<b:"<<(a<b)<<endl;
	cout<<"a==b:"<<(a==b)<<endl;
	cout<<"a!=b:"<<(a!=b)<<endl;
	cout<<"a>=b:"<<(a>=b)<<endl;
	cout<<"a<=b:"<<(a<=b)<<endl;
	
	U8::setLeakageFunction(hammingDistance);
	U16::setLeakageFunction(hammingDistance);
	
	U8 test8(1);
	test8 = U8(7);
	
	cout<<"TRACE : ";
	std::vector<double> trace = Tracer::getTrace();
	for (unsigned char i=0;i<trace.size(); i++){
		cout<<trace[i]<<" ";
	}
	cout<<endl;
	
	test8 = U8(7);
	test8 = U8(16);
	cout<<"TRACE : ";
	trace = Tracer::getTrace();
	for (unsigned char i=0;i<trace.size(); i++){
		cout<<trace[i]<<" ";
	}
	cout<<endl;
	
	U16 test16(0);
	test16 = U16(7);
	cout<<"TRACE : ";
	trace = U16::getTrace();
	for (unsigned char i=0;i<trace.size(); i++){
		cout<<trace[i]<<" ";
	}
	cout<<endl;
	
	test16 = U16(10);
	cout<<"TRACE : ";
	trace = Tracer::getTrace();
	for (unsigned char i=0;i<trace.size(); i++){
		cout<<trace[i]<<" ";
	}
	cout<<endl;
	
	Tracer::traceToFile("tracetest.csv");
	
	return 0;
}

