#pragma once
#include "RomanNumeral.h"
class FullRomanNumeral :
	public RomanNumeral
{
public:
	FullRomanNumeral(RomanIndex Index, int incrementValue, int decrementValue) : RomanNumeral(Index, incrementValue, decrementValue) {}
	
	// this handles all unit and 10 x unit data
	// this effects data in dataRomanNumeralString and localInputData
	// dataRomanNumeralString has it decimal value updates and if an error the status info
	// localInputData - the counter for this index and the last index are updated, other counter 
	//  info is used for error checking, lastIndex is used to check for pre roman numerals
	void HandleInput(dataForRomanNumeralInput& dataRomanNumeralString,
		localDataForRomanNumeralInput& localInputData) override;

private:
	const bool doesInvalidRomanNumeralPreceedThisNumeral(const int counters[(int)RomanIndex::FINAL_INDEX]);
};

