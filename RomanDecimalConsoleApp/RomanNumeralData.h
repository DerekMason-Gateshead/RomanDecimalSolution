#pragma once
#include <string>
#include "RomanNumeral.h"
#include "HalfRomanNumeral.h"
#include "FullRomanNumeral.h"

// use to store limited status information on parsing of roman numeral
enum  class eStatusCode
{
	eSUCCESS = 0,
	eFAIL_INVALID_DATA_VALUE = 1,
	eFAIL_TOO_MANY_BASE10_VALUES = 2,
	eFAIL_TOO_MANY_PRE_BASE_10_VALUES = 3,
	eFAIL_TOO_MANT_HALF_TEN_VALUES = 4,
	eFAIL_INVALID_PRE_VALUE_FOR_NUMBER = 5,
	eFAIL_PREV_USER_PRE_HIGHER_VALUE = 6,
	eFAIL_BLANK_DATA = 7,
	eFAIL_RANGE_ERROR = 8,
	eUNINTIALISED = -1
};

class RomanNumeralData
{
public:
	RomanNumeralData();
	virtual ~RomanNumeralData();

	bool IsDataValid();

	eStatusCode getStatusCode();
	void setRomanNumeralData(const std::string &data);
	int romanDecimalValue();

	bool getRomanNumeral(const std::string &sDecValue, std::string& sRomanNumeral);
	bool getRomanNumeral(int nDecimalInput, std::string& sRomanNumeral);
	
private:
	
	void getTenBaseValue(std::string& Ouput, int value, const std::string& unit, const std::string& fiveValue, const std::string& tenValue);

	// inialises status and decimal value 
	void initValues();

	// function to handle inppit roman numerals that are 1, 10, 100 etc
	bool handleHalfDecimalInput(int index, 
								int incrementValue, 
								int decrementValue, 
								int indexLastValue, 
								int counters[int(RomanIndex::FINAL_INDEX)], 
								eStatusCode& statusCode);
	// function to handle input roman numerals that are 5, 50, 500 etc
	bool handleFullDecimalInput(int index, 
								int incrementValue, 
								int decrementValue, 
								int indexLastValue, 
								int counters[int(RomanIndex::FINAL_INDEX)], 
								eStatusCode& statusCode);
private:
	bool m_bDataValid;  // set true if the current roman numeral data set is valid
	int m_nDecimalValue; // decimal value from roman numeral string
	eStatusCode m_eStatusCode; // status code giving limited information of fail
	
};

