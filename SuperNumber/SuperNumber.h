#ifndef __SUPERNUMBER_H__
#define __SUPERNUMBER_H__

#include <string>

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

	SuperNumber(double value);
	SuperNumber(float value);

	SuperNumber(std::string value);
	SuperNumber(std::wstring value);

	SuperNumber();

	// Public Destructor
	~SuperNumber();

private:
	// Private Static Fields
	static const size_t integerTypeBits;

	integerType value;
	integerType power;
};

// Template Class Hack
#include "SuperNumber.cpp"

#endif