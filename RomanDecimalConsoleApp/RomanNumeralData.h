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
	RomanNumeral* romanNumerals[512];

private:
	HalfRomanNumeral numeral_V;
	HalfRomanNumeral numeral_L;
	HalfRomanNumeral numeral_D;


	// contains status, decimal value and error codes
	dataForRomanNumeralInput m_romanNumeralDataForInput;
};

