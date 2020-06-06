#pragma once
#include "RomanNumeral.h"
class RomanNumeralValue
{
public:
	RomanNumeralValue();

	void AddValue(RomanNumeral& numeral);

	int getValue() { return decimalValue; }
	eStatusCode getStatus() { return statusCode; }
	bool getValid() { return valid; }
private: 
	void AddFiveBaseValue(RomanNumeral& numeral);
	void AddTenBaseValue(RomanNumeral& numeral);
	void setError(eStatusCode erroCode);
	int decimalValue = 0;


	int indexLastNumeral =  -1; // index of previous input value

	// contains I,V,X,L,C,D,M,5000,10000 counts
	int counters[(int)RomanIndex::FINAL_INDEX]; // running counters for each differen numeral

	bool valid = true; // is the input data valid
	eStatusCode statusCode = eStatusCode::eUNINTIALISED;  // status Code of data
	const bool doesInvalidRomanNumeralPreceedThisNumeral(int indexOfRomanNumeral, int offset);
	const bool isTenBaseValueProceededByHalfValue(int indexIfRomanNumeral);

	void checkIfPrecedeededByDecrementer(RomanNumeral& numeral, int preceederOffset);
};

