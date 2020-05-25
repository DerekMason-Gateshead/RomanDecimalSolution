#pragma once
#include "RomanNumeral.h"
class HalfRomanNumeral :
	public RomanNumeral
{
public:
	HalfRomanNumeral(int Index, int incrementValue, int decrementValue) : RomanNumeral(Index, incrementValue, decrementValue) {}
	
	void HandleInput(dataForRomanNumeralInput& dataRomanNumeralString,
						localDataForRomanNumeralInput &localInputData) override;
};


