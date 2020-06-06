#pragma once
#include <string>
#include "RomanNumeral.h"


class RomanNumeralData
{
public:
	RomanNumeralData();
	virtual ~RomanNumeralData();

	bool IsDataValid();

	eStatusCode getStatusCode();
	void setRomanNumeralData(const std::string &data);
	int romanDecimalValue();

	
private:
	// inialises status and decimal value 
	void initValues();
	RomanNumeral* ArrayOfPointersToRomanNumeralClasses[512];

private:
	RomanNumeral numeral_I;
	RomanNumeral numeral_V;
	RomanNumeral numeral_X;
	RomanNumeral numeral_L;
	RomanNumeral numeral_C; 
	RomanNumeral numeral_D;
	RomanNumeral numeral_M;
	RomanNumeral numeral_5000;
	RomanNumeral numeral_10000;

	// contains status, decimal value and error codes
	dataForRomanNumeralInput m_romanNumeralDataForInput;
};

