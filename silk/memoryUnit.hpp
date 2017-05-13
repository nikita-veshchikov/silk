#ifndef __MEMORY_UNIT_HPP__
#define __MEMORY_UNIT_HPP__

#include<iostream>
#include<cstddef>
#include<stdint.h>

#include"tracer.hpp"

/*==============================================================================
	DECLARATION
==============================================================================*/

template <typename DataType>
class MemoryUnit:public Tracer{
private:
	// atributs
	DataType _value; // the manipulated value
	static double (*_leakageFunction)(DataType oldValue, DataType newValue);
	
	
	// methods
	void copy(const MemoryUnit &mu);
	void constructLeakage(DataType oldValue, DataType newValue);
	
public:
	// --------------- Constructors & destructor ---------------
	MemoryUnit();
	MemoryUnit(DataType var);
	MemoryUnit(const MemoryUnit &mu);
	~MemoryUnit();
	
	// --------------- getters ---------------
	DataType getValue()const;
	
	// --------------- setters ---------------
	static void setLeakageFunction(double (*lf)(DataType oldValue, DataType newValue));
	
	// --------------- operators ---------------
	//assigne
	MemoryUnit& operator=(const MemoryUnit& mu);
	MemoryUnit& operator=(int val);
	MemoryUnit& operator=(unsigned val);
	MemoryUnit& operator=(long val);
	MemoryUnit& operator+=(const MemoryUnit& mu);
	MemoryUnit& operator-=(const MemoryUnit& mu);
	MemoryUnit& operator*=(const MemoryUnit& mu);
	MemoryUnit& operator/=(const MemoryUnit& mu);
	MemoryUnit& operator%=(const MemoryUnit& mu);
	MemoryUnit& operator<<=(const MemoryUnit& mu);
	MemoryUnit& operator>>=(const MemoryUnit& mu);
	MemoryUnit& operator&=(const MemoryUnit& mu);
	MemoryUnit& operator^=(const MemoryUnit& mu);
	MemoryUnit& operator|=(const MemoryUnit& mu);
	//compare
	bool operator==(const MemoryUnit&mu)const;
	bool operator==(const int& val)const;
	bool operator<=(const MemoryUnit&mu)const;
	bool operator<=(const int& val)const;
	bool operator>=(const MemoryUnit&mu)const;
	bool operator>=(const int& val)const;
	bool operator<(const MemoryUnit&mu)const;
	bool operator<(const int& val)const;
	bool operator>(const MemoryUnit&mu)const;
	bool operator>(const int& val)const;
	bool operator!=(const MemoryUnit&mu)const;
	bool operator!=(const int& val)const;
	//arithmetic
	MemoryUnit operator+(const MemoryUnit& mu);
	MemoryUnit operator+(const int& val);
	MemoryUnit operator-(const MemoryUnit& mu);
	MemoryUnit operator-(const int& val);
	MemoryUnit operator*(const MemoryUnit& mu);
	MemoryUnit operator*(const int& val);
	MemoryUnit operator*(const long& val);
	MemoryUnit operator/(const MemoryUnit& mu);
	MemoryUnit operator/(const int& mu);
	MemoryUnit operator%(const MemoryUnit& mu);
	MemoryUnit operator%(const int& val);
	MemoryUnit& operator++();
	MemoryUnit operator++(int);
	MemoryUnit& operator--();
	MemoryUnit operator--(int);
	//bitwise: &, |, ^, ~, <<, >>
	MemoryUnit operator&(const MemoryUnit& mu);
	MemoryUnit operator&(const int& val);
	MemoryUnit operator|(const MemoryUnit& mu);
	MemoryUnit operator^(const MemoryUnit& mu);
	MemoryUnit operator^(const int& val);
	MemoryUnit operator~();
	MemoryUnit operator<<(const MemoryUnit& shift);
	MemoryUnit operator<<(int shift);
	MemoryUnit operator>>(const MemoryUnit& shift);
	MemoryUnit operator>>(int shift);
	// convert
	operator ptrdiff_t()const;
	/*operator unsigned int()const;
	operator int()const;*/
};

// external operators
//stream
template <typename DataType>
std::ostream& operator<<(std::ostream& out, const MemoryUnit<DataType> &mu){
	out<<mu.getValue();
	return out;
}

template <typename DataType>
MemoryUnit<DataType> operator^(const MemoryUnit<DataType>& mu1, const MemoryUnit<DataType>& mu2){
	return MemoryUnit<DataType>(mu1.getValue() ^ mu2.getValue());
}

/*==============================================================================
	IMPLEMENTATION
==============================================================================*/

// --------------- Constructors & destructor ---------------

template <typename DataType>
double (*MemoryUnit<DataType>::_leakageFunction)(DataType oldValue, DataType newValue) = NULL;

template <typename DataType>
MemoryUnit<DataType>::MemoryUnit(){}

template <typename DataType>
MemoryUnit<DataType>::MemoryUnit(DataType val):_value(val){
	constructLeakage((DataType)(0), val);
}

template <typename DataType>
MemoryUnit<DataType>::MemoryUnit(const MemoryUnit<DataType> &mu):Tracer(){
	copy(mu);
}

template <typename DataType>
MemoryUnit<DataType>::~MemoryUnit(){
	//nothing to do here
}

// --------------- getters ---------------
template <typename DataType>
DataType MemoryUnit<DataType>::getValue()const{
	return _value;
}

// --------------- setters ---------------
template <typename DataType>
void MemoryUnit<DataType>::setLeakageFunction(double (*lf)(DataType oldValue, DataType newValue)){
	_leakageFunction = lf;
}

// --------------- operators ---------------

// assigne
template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator=(const MemoryUnit<DataType>& mu){
	if (this != &mu){
		copy(mu);
	}
	return (*this);
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator=(int val){
	return (operator=(MemoryUnit<DataType>(val)));
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator=(unsigned val){
	return (operator=(MemoryUnit<DataType>(val)));
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator=(long val){
	return (operator=(MemoryUnit<DataType>(val)));
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator+=(const MemoryUnit<DataType>& mu){
	DataType tmp = _value;
	_value+=mu._value;
	constructLeakage(tmp, _value);
	return *this;
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator-=(const MemoryUnit<DataType>& mu){
	DataType tmp = _value;
	_value-=mu._value;
	constructLeakage(tmp, _value);
	return *this;
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator*=(const MemoryUnit<DataType>& mu){
	DataType tmp = _value;
	_value*=mu._value;
	constructLeakage(tmp, _value);
	return *this;
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator/=(const MemoryUnit<DataType>& mu){
	DataType tmp = _value;
	_value/=mu._value;
	constructLeakage(tmp, _value);
	return *this;
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator%=(const MemoryUnit<DataType>& mu){
	DataType tmp = _value;
	_value%=mu._value;
	constructLeakage(tmp, _value);
	return *this;
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator<<=(const MemoryUnit<DataType>& mu){
	DataType tmp = _value;
	_value<<=mu._value;
	constructLeakage(tmp, _value);
	return *this;
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator>>=(const MemoryUnit<DataType>& mu){
	DataType tmp = _value;
	_value>>=mu._value;
	constructLeakage(tmp, _value);
	return *this;
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator&=(const MemoryUnit<DataType>& mu){
	DataType tmp = _value;
	_value&=mu._value;
	constructLeakage(tmp, _value);
	return *this;
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator^=(const MemoryUnit<DataType>& mu){
	DataType tmp = _value;
	_value^=mu._value;
	constructLeakage(tmp, _value);
	return *this;
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator|=(const MemoryUnit<DataType>& mu){
	DataType tmp = _value;
	_value|=mu._value;
	constructLeakage(tmp, _value);
	return *this;
}

//arithmetic
template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator+(const MemoryUnit<DataType>& mu){
	return MemoryUnit<DataType>(_value+mu._value);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator+(const int& val){
	return MemoryUnit<DataType>(_value+val);
}


template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator-(const MemoryUnit<DataType>& mu){
	return MemoryUnit<DataType>(_value-mu._value);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator-(const int& val){
	return MemoryUnit<DataType>(_value-val);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator*(const MemoryUnit<DataType>& mu){
	return MemoryUnit<DataType>(_value*mu._value);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator*(const int& val){
	return MemoryUnit<DataType>(_value*val);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator*(const long& val){
	return MemoryUnit<DataType>(_value*val);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator/(const MemoryUnit<DataType>& mu){
	return MemoryUnit<DataType>(_value/mu._value);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator/(const int& val){
	return MemoryUnit<DataType>(_value/val);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator%(const MemoryUnit<DataType>& mu){
	return MemoryUnit<DataType>(_value%mu._value);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator%(const int& val){
	return MemoryUnit<DataType>(_value%val);
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator++(){
	++_value;
	constructLeakage(_value-1, _value);
	return *this;
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator++(int){
	MemoryUnit<DataType> tmp(*this);
	operator++();
	return tmp;
}

template <typename DataType>
MemoryUnit<DataType>& MemoryUnit<DataType>::operator--(){
	--_value;
	constructLeakage(_value+1, _value);
	return *this;
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator--(int){
	MemoryUnit<DataType> tmp(*this);
	operator--();
	return tmp;
}

//compare
template <typename DataType>
bool MemoryUnit<DataType>::operator==(const MemoryUnit<DataType>& mu)const{
	return _value == mu._value;
}

template <typename DataType>
bool MemoryUnit<DataType>::operator==(const int& val)const{
	return _value == val;
}

template <typename DataType>
bool MemoryUnit<DataType>::operator!=(const MemoryUnit<DataType>& mu)const{
	return !operator==(mu);
}

template <typename DataType>
bool MemoryUnit<DataType>::operator!=(const int& val)const{
	return !operator==(val);
}

template <typename DataType>
bool MemoryUnit<DataType>::operator<=(const MemoryUnit<DataType>& mu)const{
	return !(*this>mu);
}

template <typename DataType>
bool MemoryUnit<DataType>::operator<=(const int& val)const{
	return _value <= val;
}

template <typename DataType>
bool MemoryUnit<DataType>::operator>=(const MemoryUnit<DataType>& mu)const{
	return !(*this<mu);
}

template <typename DataType>
bool MemoryUnit<DataType>::operator>=(const int& val)const{
	return _value >= val;
}

template <typename DataType>
bool MemoryUnit<DataType>::operator<(const MemoryUnit<DataType>& mu)const{
	return _value < mu._value;
}

template <typename DataType>
bool MemoryUnit<DataType>::operator<(const int& val)const{
	return _value < val;
}

template <typename DataType>
bool MemoryUnit<DataType>::operator>(const MemoryUnit<DataType>& mu)const{
	return mu < (*this);
}

template <typename DataType>
bool MemoryUnit<DataType>::operator>(const int& val)const{
	return _value > val;
}


//bitwise: &, |, ^, ~, <<, >>
template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator&(const MemoryUnit<DataType>& mu){
	return MemoryUnit<DataType>(_value&mu._value);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator&(const int& val){
	return MemoryUnit<DataType>(_value&val);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator|(const MemoryUnit<DataType>& mu){
	return MemoryUnit<DataType>(_value|mu._value);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator^(const MemoryUnit<DataType>& mu){
	return MemoryUnit<DataType>(_value^mu._value);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator^(const int& val){
	return MemoryUnit<DataType>(_value^val);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator~(){
	return MemoryUnit<DataType>(~_value);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator<<(const MemoryUnit<DataType>& shift){
	return MemoryUnit<DataType>(_value<<shift._value);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator<<(int shift){
	return MemoryUnit<DataType>(_value<<shift);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator>>(const MemoryUnit<DataType>& shift){
	return MemoryUnit<DataType>(_value>>shift._value);
}

template <typename DataType>
MemoryUnit<DataType> MemoryUnit<DataType>::operator>>(int shift){
	return MemoryUnit<DataType>(_value>>shift);
}

// convert
template <typename DataType>
MemoryUnit<DataType>::operator ptrdiff_t()const{
	return _value;
}

/*
template <typename DataType>
MemoryUnit<DataType>::operator unsigned int()const{
	return (unsigned int)_value;
}

template <typename DataType>
MemoryUnit<DataType>::operator int()const{
	return (int)_value;
}
*/
// Private methods
template <typename DataType>
void MemoryUnit<DataType>::copy(const MemoryUnit<DataType>& mu){
	constructLeakage(_value, mu._value);
	_value = mu._value;
}

template <typename DataType>
void MemoryUnit<DataType>::constructLeakage(DataType oldValue, DataType newValue){
	if(_leakageFunction != NULL and _leakagePointsNbr>0){
		double leakage = _leakageFunction(oldValue, newValue);
		std::vector<double> operationLeakage(_leakagePointsNbr, leakage);
		
		if (_leakageDistributionFunc != NULL){
			double step = double(_leakageInterval)/(_leakagePointsNbr+1);
			for (unsigned i=0;i<_leakagePointsNbr;++i){
				operationLeakage[i] = _leakageDistributionFunc(leakage, (i+1)*step);
			}
		}
		unsigned size = _trace.size();
		unsigned overlap = _leakageOverlap;
		if (size == 0){
			overlap = 0;
		}
		for(unsigned i=overlap;i!=0;--i){
			// TODO : add possibility of combination for overlap other than "+"
			_trace[size-i] += operationLeakage[overlap-i];
		}
		_trace.insert(_trace.end(), operationLeakage.begin()+overlap, operationLeakage.end());
	}
}

#endif //__MEMORY_UNIT_HPP__
