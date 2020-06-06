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

bool RomanNumeral::IsHalfValue()
{
	int theIncrementValue = incrementValue;

	while (theIncrementValue >= 10)
	{
		theIncrementValue = theIncrementValue / 10;
	}

	if (theIncrementValue == 1)
	{
		return false;
	}
	return true;
}
