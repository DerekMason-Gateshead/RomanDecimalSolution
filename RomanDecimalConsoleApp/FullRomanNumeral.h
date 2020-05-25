#pragma once
#include "RomanNumeral.h"
class FullRomanNumeral :
	public RomanNumeral
{
public:
	FullRomanNumeral(int Index, int incrementValue, int decrementValue) : RomanNumeral(Index, incrementValue, decrementValue) {}
	void HandleInput(dataForRomanNumeralInput& dataRomanNumeralString,
		localDataForRomanNumeralInput& localInputData) override;
};

