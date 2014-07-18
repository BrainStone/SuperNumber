#ifndef __SUPERNUMBER_H__
#define __SUPERNUMBER_H__

#include <string>
#include <locale>
#include <codecvt>
#include <map>
#include <stdexcept>

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

	SuperNumber(std::string value, unsigned short radix = 10);
	SuperNumber(std::wstring value, unsigned short radix = 10);

	SuperNumber();

	// Public Destructor
	~SuperNumber();

private:
	// Private Static Fields
	static const size_t integerTypeBits;

	// Private Methods
	void initializeFromUnsignedLongLong(unsigned long long value, bool negative = false);

	// Private Fields
	integerType value;
	integerType power;
};

// Template Class Hack
#include "SuperNumber.cpp"

#endif