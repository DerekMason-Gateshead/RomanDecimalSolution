#include "RomanNumeral.h"

RomanNumeral::RomanNumeral(RomanIndex Pindex, int PincrementValue, int PdecrementValue)
{
	indexOfRomanNumeral = Pindex;
	incrementValue = PincrementValue;
	decrementValue = PdecrementValue;
}

RomanNumeral::~RomanNumeral()
{
}
