#ifndef __SUPERNUMBER_CPP__
#define __SUPERNUMBER_CPP__

#include "SuperNumber.h"

// Static Fields

template<typename integerType>
const size_t SuperNumber<integerType>::integerTypeBits = sizeof(integerType) * 8;

// Constructors

template<typename integerType>
SuperNumber<integerType>::SuperNumber()
	: value(0), power(0)
{}

// Destructor

template<typename integerType>
SuperNumber<integerType>::~SuperNumber()
{
}

#endif