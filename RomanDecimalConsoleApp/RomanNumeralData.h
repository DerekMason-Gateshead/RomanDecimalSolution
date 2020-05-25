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

	// function to handle inppit roman numerals that are 1, 10, 100 etc
//	void handleHalfDecimalInput(int index, 
//								int incrementValue, 
//								int decrementValue, 
//								dataForRomanNumeralInput& dataRomanNumeralString,
//								localDataForRomanNumeralInput& localInputData);

	// function to handle input roman numerals that are 5, 50, 500 etc
//	void handleFullDecimalInput(int index, 
//								int incrementValue, 
//								int decrementValue, 
//								dataForRomanNumeralInput& dataRomanNumeralString,
//								localDataForRomanNumeralInput& localInputData);

private:
//	bool m_bDataValid;  // set true if the current roman numeral data set is valid
//	int m_nDecimalValue; // decimal value from roman numeral string
//	eStatusCode m_eStatusCode; // status code giving limited information of fail
	
	dataForRomanNumeralInput m_romanNumeralDataForInput;
};

