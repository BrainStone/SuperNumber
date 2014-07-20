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
const SuperNumber<integerType> SuperNumber<integerType>::operator+() const {
	return SuperNumber<integerType>(*this);
}

template<typename integerType>
const SuperNumber<integerType> SuperNumber<integerType>::operator-() const {
	SuperNumber<integerType> result(*this);

	result.value = -result.value;

	return result;
}

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
		this->value = (integerType)(value << (integerType(63) - firstOneBit) >> (65 - integerTypeBits));
		this->value = (negative) ? -this->value : this->value;
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
		value = (integerType)(value << ((integerTypeBits - 2) - firstOneBit));
		value = (negative) ? -value : value;
	}
}

// Mathematical operations

template<typename integerType>
const SuperNumber<integerType> operator+(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs) {
	SuperNumber<integerType> tmp_lhs(lhs);
	SuperNumber<integerType> tmp_rhs(rhs);

	bool negative_lhs = tmp_lhs.value < 0;
	bool negative_rhs = tmp_rhs.value < 0;

	tmp_lhs.value = (negative_lhs) ? -tmp_lhs.value : tmp_lhs.value;
	tmp_rhs.value = (negative_rhs) ? -tmp_rhs.value : tmp_rhs.value;

	if (negative_rhs ^ negative_lhs) {
		return (negative_lhs) ? (tmp_rhs - tmp_lhs) : (tmp_lhs - tmp_rhs);
	}

	bool negative = negative_lhs && negative_rhs;

	SuperNumber<integerType> result;

	result.power = std::max(tmp_lhs.power, tmp_rhs.power);
	integerType lhs_value = tmp_lhs.value >> (result.power - tmp_lhs.power);
	integerType rhs_value = tmp_rhs.value >> (result.power - tmp_rhs.power);

	result.value = lhs_value + rhs_value;

	if ((result.value < lhs_value) || (result.value < rhs_value)) {
		lhs_value >>= 1;
		rhs_value >>= 1;

		result.value = lhs_value + rhs_value;
		result.power++;
	}

	return (negative) ? -result : result;
}

template<typename integerType>
const SuperNumber<integerType> operator-(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs) {
	SuperNumber<integerType> tmp_lhs(lhs);
	SuperNumber<integerType> tmp_rhs(rhs);

	bool negative_lhs = tmp_lhs.value < 0;
	bool negative_rhs = tmp_rhs.value < 0;

	tmp_lhs.value = (negative_lhs) ? -tmp_lhs.value : tmp_lhs.value;
	tmp_rhs.value = (negative_rhs) ? -tmp_rhs.value : tmp_rhs.value;

	if (negative_rhs ^ negative_lhs) {
		return (negative_lhs) ? -(tmp_lhs + tmp_rhs) : (tmp_lhs + tmp_rhs);
	}

	bool negative = negative_lhs && negative_rhs;

	SuperNumber<integerType> result;

	result.power = std::max(tmp_lhs.power, tmp_rhs.power);
	integerType lhs_value = tmp_lhs.value >> (result.power - tmp_lhs.power);
	integerType rhs_value = tmp_rhs.value >> (result.power - tmp_rhs.power);

	result.value = lhs_value - rhs_value;

	result.normalizeNumber();
	return (negative) ? -result : result;
}

template<typename integerType>
const SuperNumber<integerType> operator*(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs) {
	SuperNumber<integerType> tmp_lhs(lhs);
	SuperNumber<integerType> tmp_rhs(rhs);

	bool negative_lhs = tmp_lhs.value < 0;
	bool negative_rhs = tmp_rhs.value < 0;

	tmp_lhs.value = (negative_lhs) ? -tmp_lhs.value : tmp_lhs.value;
	tmp_rhs.value = (negative_rhs) ? -tmp_rhs.value : tmp_rhs.value;

	bool negative = negative_lhs ^ negative_rhs;

	SuperNumber<integerType> result;

	result.power = (tmp_lhs.power + tmp_rhs.power) + (SuperNumber<integerType>::integerTypeBits - 2);

	integerType bitLimit = SuperNumber<integerType>::integerTypeBits - 2;
	integerType tmpAddition;

	for (integerType i = bitLimit; i >= 0; i--) {
		if ((tmp_rhs.value >> i) & 1) {
			tmpAddition = tmp_lhs.value >> (bitLimit - i);

			result.value += tmpAddition;

			if (result.value < tmpAddition) {
				result.value -= tmpAddition;

				result.value >>= 1;
				result.value += (tmpAddition >> 1);

				bitLimit++;
				result.power++;
			}
		}
	}

	result.normalizeNumber();
	return (negative) ? -result : result;
}

template<typename integerType>
const SuperNumber<integerType> operator/(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs) {
	// TODO: Multiplication
}

#endif