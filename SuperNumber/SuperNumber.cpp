#ifndef __SUPERNUMBER_CPP__
#define __SUPERNUMBER_CPP__

#include "SuperNumber.h"

// Static Fields

template<typename integerType>
const size_t SuperNumber<integerType>::integerTypeBits = sizeof(integerType)* 8;

// Constructors

template<typename integerType>
SuperNumber<integerType>::SuperNumber(long long value) {
	bool negative = value < 0LL;
	initializeFromUnsignedLongLong((negative) ? -value : value, negative);
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
	initializeFromUnsignedLongLong(value);
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
SuperNumber<integerType>::SuperNumber(float value) : SuperNumber((double)value) {}

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

// Methods

template<typename integerType>
void SuperNumber<integerType>::initializeFromUnsignedLongLong(unsigned long long value, bool negative) {
	if (value == 0LL) {
		this->value = 0;
		this->power = 0;
	}
	else {
		integerType firstOneBit = 63;
		for (; !(value >> firstOneBit); firstOneBit--) {}

		this->power = firstOneBit - integerTypeBits + 2;
		this->value = (integerType)(value << (integerType(63) - firstOneBit) >> (65 - integerTypeBits))
			// Set negative flag
			| (negative << (integerTypeBits - 1));
	}
}

#endif