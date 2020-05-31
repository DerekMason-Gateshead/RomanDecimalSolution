#pragma once
#include <string>
#include "RomanNumeral.h"
#include "HalfRomanNumeral.h"
#include "FullRomanNumeral.h"



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
	FullRomanNumeral numeral_I;
	HalfRomanNumeral numeral_V;
	FullRomanNumeral numeral_X;
	HalfRomanNumeral numeral_L;
	FullRomanNumeral numeral_C; 
	HalfRomanNumeral numeral_D;
	FullRomanNumeral numeral_M;
	HalfRomanNumeral numeral_5000;
	FullRomanNumeral numeral_10000;

	// contains status, decimal value and error codes
	dataForRomanNumeralInput m_romanNumeralDataForInput;
};

