#ifndef __SUPERNUMBER_H__
#define __SUPERNUMBER_H__

#include <string>
#include <locale>
#include <codecvt>
#include <map>
#include <stdexcept>
#include <algorithm>
#include <limits>

template<typename integerType>
class SuperNumber {
public:
	// Public Constructors
	SuperNumber(long long value);
	SuperNumber(long value);
	SuperNumber(int value);
	SuperNumber(short value);
	SuperNumber(signed char value);

	SuperNumber(unsigned long long value);
	SuperNumber(unsigned long value);
	SuperNumber(unsigned int value);
	SuperNumber(unsigned short value);
	SuperNumber(char value);

	SuperNumber(long double value);
	SuperNumber(double value);
	SuperNumber(float value);

	SuperNumber(const std::string &value, unsigned short radix = 10);
	SuperNumber(const std::wstring &value, unsigned short radix = 10);

	SuperNumber();

	// Public Destructor
	~SuperNumber();

	// Public Methods
	std::string to_String() const {
		return std::to_string(value) + "\n" + std::to_string(power) + "\n" + std::to_string(value >> (-power)) + "\n";
	}

	const SuperNumber<integerType> operator+() const;
	const SuperNumber<integerType> operator-() const;

	SuperNumber<integerType>& operator+=(SuperNumber<integerType> const& rhs);
	SuperNumber<integerType>& operator-=(SuperNumber<integerType> const& rhs);
	SuperNumber<integerType>& operator*=(SuperNumber<integerType> const& rhs);
	SuperNumber<integerType>& operator/=(SuperNumber<integerType> const& rhs);

	// Public Friends
	template<typename integerType>
	friend const SuperNumber<integerType> operator+(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);
	template<typename integerType>
	friend const SuperNumber<integerType> operator-(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);
	template<typename integerType>
	friend const SuperNumber<integerType> operator*(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);
	template<typename integerType>
	friend const SuperNumber<integerType> operator/(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);

	template<typename integerType>
	friend bool operator==(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);
	template<typename integerType>
	friend bool operator!=(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);

	template<typename integerType>
	friend bool operator<(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);
	template<typename integerType>
	friend bool operator<=(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);
	template<typename integerType>
	friend bool operator>(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);
	template<typename integerType>
	friend bool operator>=(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);


private:
	// Private Static Fields
	static const size_t integerTypeBits;
	static const integerType minValue;
	static const integerType maxValue;

	// Private Methods
	void initializeFromUnsignedLongLong(unsigned long long value, bool negative = false);
	void normalizeNumber();

	// Private Fields
	integerType value;
	integerType power;
};

// Mathematical operations
template<typename integerType>
const SuperNumber<integerType> operator+(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);
template<typename integerType>
const SuperNumber<integerType> operator-(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);
template<typename integerType>
const SuperNumber<integerType> operator*(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);
template<typename integerType>
const SuperNumber<integerType> operator/(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);

template<typename integerType>
bool operator==(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);
template<typename integerType>
bool operator!=(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);

template<typename integerType>
bool operator<(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);
template<typename integerType>
bool operator<=(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);
template<typename integerType>
bool operator>(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);
template<typename integerType>
bool operator>=(SuperNumber<integerType> const& lhs, SuperNumber<integerType> const& rhs);

// Template Class Hack
#include "SuperNumber.cpp"

#endif