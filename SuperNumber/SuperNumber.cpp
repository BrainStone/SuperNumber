#ifndef __SUPERNUMBER_CPP__
#define __SUPERNUMBER_CPP__

#include "SuperNumber.h"

// Static Fields

template<typename integerType>
const size_t SuperNumber<integerType>::integerTypeBits = sizeof(integerType) * 8;

// Constructors

template<typename integerType>
SuperNumber<integerType>::SuperNumber(long long value) {
	// TODO: Fill the value
}

template<typename integerType>
SuperNumber<integerType>::SuperNumber(long value) : SuperNumber((long long)value) {}
template<typename integerType>
SuperNumber<integerType>::SuperNumber(int value) : SuperNumber((long long)value) {}
template<typename integerType>
SuperNumber<integerType>::SuperNumber(short value) : SuperNumber((long long)value) {}
template<typename integerType>
SuperNumber<integerType>::SuperNumber(signed char value) : SuperNumber((long long)value) {}

template<typename integerType>
SuperNumber<integerType>::SuperNumber(unsigned long long value) {
	// TODO: Fill the value
}

template<typename integerType>
SuperNumber<integerType>::SuperNumber(unsigned long value) : SuperNumber((unsigned long long)value) {}
template<typename integerType>
SuperNumber<integerType>::SuperNumber(unsigned int value) : SuperNumber((unsigned long long)value) {}
template<typename integerType>
SuperNumber<integerType>::SuperNumber(unsigned short value) : SuperNumber((unsigned long long)value) {}
template<typename integerType>
SuperNumber<integerType>::SuperNumber(char value) : SuperNumber((unsigned long long)value) {}

template<typename integerType>
SuperNumber<integerType>::SuperNumber(double value) {
	// TODO: Fill the value
}

template<typename integerType>
SuperNumber<integerType>::SuperNumber(float value) : SuperNumber((double) value) {}

template<typename integerType>
SuperNumber<integerType>::SuperNumber(std::string value) {
	// TODO: Fill the value
}

template<typename integerType>
SuperNumber<integerType>::SuperNumber(std::wstring value) {
	// TODO: Fill the value
}

template<typename integerType>
SuperNumber<integerType>::SuperNumber() : value(0), power(0) {}

// Destructor

template<typename integerType>
SuperNumber<integerType>::~SuperNumber()
{
}

#endif