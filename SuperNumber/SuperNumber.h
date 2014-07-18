#ifndef __SUPERNUMBER_H__
#define __SUPERNUMBER_H__

template<typename integerType>
class SuperNumber
{
public:
	// Public Constructors
	SuperNumber(long long value);
	SuperNumber(unsigned long long value);

	SuperNumber(long value);
	SuperNumber(unsigned long value);

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