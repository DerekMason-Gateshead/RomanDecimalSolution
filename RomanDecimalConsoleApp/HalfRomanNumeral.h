#pragma once
#include "RomanNumeral.h"
class HalfRomanNumeral :
	public RomanNumeral
{
public:
	HalfRomanNumeral(int Index, int incrementValue, int decrementValue) : RomanNumeral(Index, incrementValue, decrementValue) {}
	
	// this handles all half units, i.e 5, 50, 500 etc
	// this effects data in dataRomanNumeralString and localInputData
	// dataRomanNumeralString has it decimal value updates and if an error the status info
	// localInputData - the counter for this index and the last index are updated, other counter 
	//  info is used for error checking, lastIndex is used to check for pre roman numerals
	void HandleInput(dataForRomanNumeralInput& dataRomanNumeralString,
						localDataForRomanNumeralInput &localInputData) override;
};


