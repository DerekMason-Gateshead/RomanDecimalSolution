#pragma once
#include "RomanNumeral.h"
class FullRomanNumeral :
	public RomanNumeral
{
public:
	void HandleInput(dataForRomanNumeralInput& dataRomanNumeralString,
		localDataForRomanNumeralInput& localInputData) override;
};

