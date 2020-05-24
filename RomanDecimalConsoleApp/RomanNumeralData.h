#pragma once
#include <string>
#include "RomanNumeral.h"
#include "HalfRomanNumeral.h"
#include <vector>

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

enum class ROMAN_NUMERAL_VALUE
{
	Undef = 0,
	I = 1,
	V = 5,
	X = 10,
	L = 50,
	C = 100,
	D = 500,
	M = 1000,
	ROMAN5000 = 5000,
	ROMAN10000 = 10000
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
private:
	HalfRomanNumeral V;

	void lastRomanNumeral_I(); // called when a V or X is preceeded by an I
	void lastRomanNumeral_X();
	void lastRomanNumeral_C();
	void lastRomanNumeral_M();
	void initValues();

	void handleHalfDecimalInput(int index, int incrementValue, int decrementValue, int indexLastValue, int counters[int(RomanIndex::FINAL_INDEX)]);

	void handleRomanNumeral_I();  // Handles the receit of roman 1 
	void handleRomanNumeral_X(); // Handles the receit of roman number 10 (X)
	void handleRomanNumeral_C(); // handle roman numeral 100 C
	void handleRomanNumeral_M(); // handle roman numeral M 1000

private:
	bool m_bDataValid;
	
	int m_nDecimalValue;

	eStatusCode m_eStatusCode;

   int m_RomanNumeralCounts[int(RomanIndex::FINAL_INDEX)];  // needs to contain I,V,X,L,C,D,M,5000,10000 counts




	int m_nCountRomanNumeral5000inInput; // V with line above counter for 5000 roman numerals we use ^V or ^v
	int m_nCountRomanNumeral_10000inInput; // X with line above for 10000 roman numerals - we use ^X or ^x

	ROMAN_NUMERAL_VALUE m_nLastRomanNumeral;
};

