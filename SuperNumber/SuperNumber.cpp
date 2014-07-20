#ifndef __SUPERNUMBER_CPP__
#define __SUPERNUMBER_CPP__

#include "SuperNumber.h"

// Static Fields

template<typename integerType>
const size_t SuperNumber<integerType>::integerTypeBits = sizeof(integerType)* 8;

template<typename integerType>
const integerType SuperNumber<integerType>::minValue = std::numeric_limits<integerType>::lowest();
template<typename integerType>
const integerType SuperNumber<integerType>::maxValue = std::numeric_limits<integerType>::max();

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
SuperNumber<integerType>::SuperNumber(long double value) {
	// TODO: Fill the value
}

template<typename integerType>
SuperNumber<integerType>::SuperNumber(double value) : SuperNumber((long double)value) {}
template<typename integerType>
SuperNumber<integerType>::SuperNumber(float value) : SuperNumber((long double)value) {}

template<typename integerType>
SuperNumber<integerType>::SuperNumber(const std::string &value, unsigned short radix) : SuperNumber(std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().from_bytes(value), radix) {}

#include <iostream>

template<typename integerType>
SuperNumber<integerType>::SuperNumber(const std::wstring &value, unsigned short radix) {
	if (radix > 36) {
		throw std::out_of_range("The radix was " + std::to_string(radix) + ". That is bigger than 36. The maxiumum radix.");
	}
	else if (radix < 2) {
		throw std::out_of_range("The radix was " + std::to_string(radix) + ". That is less than 2. The minimum radix.");
	}

	std::map<wchar_t, short> allowedCharacters;

	wchar_t i;
	for (i = 0; i < 10; i++) {
		allowedCharacters[L'0' + i] = i;
	}
	for (i = 10; i < radix; i++) {
		allowedCharacters[L'7' + i] = i;
		allowedCharacters[L'W' + i] = i;
	}
	allowedCharacters[L'.'] = -1;

	// TODO: Fill the value
}

template<typename integerType>
SuperNumber<integerType>::SuperNumber() : value(0), power(minValue) {}

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
		this->power = minValue;
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

template<typename integerType>
void SuperNumber<integerType>::normalizeNumber() {
	if (value == 0LL) {
		this->value = 0;
		this->power = minValue;
	}
	else {
		bool negative = value < 0;
		value = (negative) ? -value : value;

		integerType firstOneBit = integerTypeBits - 2;
		for (; !(value >> firstOneBit); firstOneBit--) {}

		power += firstOneBit - integerTypeBits + 2;
		value = (integerType)(value << ((integerTypeBits - 2) - firstOneBit))
			// Set negative flag
			| (negative << (integerTypeBits - 1));
	}
}

// Mathematical operations
template<typename integerType>
const SuperNumber<integerType> operator+(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs) {
	SuperNumber<integerType> result;

	result.power = std::max(lhs.power, rhs.power);
	integerType lhs_value = lhs.value >> (result.power - lhs.power);
	integerType rhs_value = rhs.value >> (result.power - rhs.power);

	result.value = lhs_value + rhs_value;

	if ((result.value < lhs_value) || (result.value < rhs_value)) {
		lhs_value >>= 1;
		rhs_value >>= 1;

		result.value = lhs_value + rhs_value;
		result.power++;
	}

	return result;
}

template<typename integerType>
const SuperNumber<integerType> operator-(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs) {
	SuperNumber<integerType> result;

	result.power = std::max(lhs.power, rhs.power);
	integerType lhs_value = lhs.value >> (result.power - lhs.power);
	integerType rhs_value = rhs.value >> (result.power - rhs.power);

	result.value = lhs_value - rhs_value;

	result.normalizeNumber();
	return result;
}

template<typename integerType>
const SuperNumber<integerType> operator*(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs) {
	// TODO: Not working yet!
	SuperNumber<integerType> result;

	result.power = (lhs.power + rhs.power)/* + (SuperNumber<integerType>::integerTypeBits)*/;

	int bitLimit = SuperNumber<integerType>::integerTypeBits - 2;
	for (int i = bitLimit; i >= 0; i--) {
		if ((rhs.value >> i) & 1) {
			result.value += lhs.value >> (bitLimit - i);

			if (result.value < lhs.value) {
				result.value -= lhs.value >> (bitLimit - i);

				bitLimit++;

				result.value += lhs.value >> (bitLimit - i);
				result.power++;
			}
		}
	}

	result.normalizeNumber();
	return result;
}

template<typename integerType>
const SuperNumber<integerType> operator/(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs) {
	// TODO: Multiplication
}

#endif