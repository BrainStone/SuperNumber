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
SuperNumber<integerType>::SuperNumber(const std::string &value, unsigned short radix) : SuperNumber<integerType>() {
	if (radix > 36) {
		throw std::out_of_range("The radix was " + std::to_string(radix) + ". That is bigger than 36. The maxiumum radix.");
	}
	else if (radix < 2) {
		throw std::out_of_range("The radix was " + std::to_string(radix) + ". That is less than 2. The minimum radix.");
	}

	std::map<char, SuperNumber<integerType>> allowedCharacters;
	SuperNumber<integerType> minus1(-1);

	char i;
	for (i = 0; i < 10; i++) {
		allowedCharacters['0' + i] = i;
	}
	for (i = 10; i < radix; i++) {
		allowedCharacters['7' + i] = i;
		allowedCharacters['W' + i] = i;
	}
	allowedCharacters['.'] = minus1;

	std::map<char, SuperNumber<integerType>>::const_iterator it;
	std::map<char, SuperNumber<integerType>>::const_iterator end(allowedCharacters.end());
	size_t stringSize = value.size();
	bool commaFound = false;
	SuperNumber<integerType> Radix(radix);
	SuperNumber<integerType> Divisor(1);

	for (size_t i = 0; i < stringSize; i++) {
		it = allowedCharacters.find(value[i]);
		if (it != end) {
			if (commaFound) {
				if (it->second == minus1) {
					throw invalid_argument("\"" + value + "\" could not be parsed as a number!");
				}
				Divisor *= Radix;
				*this += it->second / Divisor;
			}
			else {
				if (it->second == minus1) {
					commaFound = true;
				}
				else{
					*this *= Radix;
					*this += it->second;
				}
			}
		}
		else {
			throw invalid_argument("\"" + value + "\" could not be parsed as a number!");
		}
	}
}

template<typename integerType>
SuperNumber<integerType>::SuperNumber(const std::wstring &value, unsigned short radix) : SuperNumber(std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(value), radix) {}

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
SuperNumber<integerType>& SuperNumber<integerType>::operator+=(SuperNumber<integerType> const& rhs) {
	*this = *this + rhs;

	return *this;
}

template<typename integerType>
SuperNumber<integerType>& SuperNumber<integerType>::operator-=(SuperNumber<integerType> const& rhs) {
	*this = *this - rhs;

	return *this;
}

template<typename integerType>
SuperNumber<integerType>& SuperNumber<integerType>::operator*=(SuperNumber<integerType> const& rhs) {
	*this = *this * rhs;

	return *this;
}

template<typename integerType>
SuperNumber<integerType>& SuperNumber<integerType>::operator/=(SuperNumber<integerType> const& rhs) {
	*this = *this / rhs;

	return *this;
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

		integerType firstOneBit = (integerType)integerTypeBits - 2;
		for (; !(value >> firstOneBit); firstOneBit--) {}

		power += firstOneBit - (integerType)integerTypeBits + 2;
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

	integerType bitLimit = (integerType)SuperNumber<integerType>::integerTypeBits - 2;
	integerType tmpAddition;
	result.power = (tmp_lhs.power + tmp_rhs.power) + bitLimit;

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
	SuperNumber<integerType> tmp_lhs(lhs);
	SuperNumber<integerType> tmp_rhs(rhs);

	bool negative_lhs = tmp_lhs.value < 0;
	bool negative_rhs = tmp_rhs.value < 0;

	tmp_lhs.value = (negative_lhs) ? -tmp_lhs.value : tmp_lhs.value;
	tmp_rhs.value = (negative_rhs) ? -tmp_rhs.value : tmp_rhs.value;

	bool negative = negative_lhs ^ negative_rhs;

	SuperNumber<integerType> result;

	integerType bitLimit = (integerType)SuperNumber<integerType>::integerTypeBits - 2;
	result.power = (tmp_lhs.power + tmp_rhs.power) + bitLimit;

	// TODO: Division

	result.normalizeNumber();
	return (negative) ? -result : result;
}

template<typename integerType>
bool operator==(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs) {
	return (lhs.value == rhs.value) && (lhs.power == rhs.power);
}

template<typename integerType>
bool operator!=(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs) {
	return (lhs.value != rhs.value) || (lhs.power != rhs.power);
}

template<typename integerType>
bool operator<(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs) {
	if (lhs.power == rhs.power) {
		return lhs.value < rhs.value;
	}
	else {
		return lhs.power < rhs.power;
	}
}

template<typename integerType>
bool operator<=(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs) {
	if (lhs.power == rhs.power) {
		return lhs.value <= rhs.value;
	}
	else {
		return lhs.power < rhs.power;
	}
}

template<typename integerType>
bool operator>(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs) {
	return rhs < lhs;
}

template<typename integerType>
bool operator>=(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs) {
	return rhs <= lhs;
}

#endif