#pragma once
#include "RomanNumeral.h"
class HalfRomanNumeral :
	public RomanNumeral
{
public:
	void HandleInput(dataForRomanNumeralInput& dataRomanNumeralString,
						localDataForRomanNumeralInput &localInputData) override;
};


