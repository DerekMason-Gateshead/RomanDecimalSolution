#pragma once
#include <string>

enum  eStatusCode
{
	eSUCCESS = 0,
	eFAIL_INVALID_DATA_VALUE = 1,
	eFAIL_TOO_MANY_BASE10_VALUES = 2,
	eFAIL_TOO_MANY_PRE_BASE_10_VALUES = 3,
	eFAIL_TOO_MANT_HALF_TEN_VALUES = 4,
	eFAIL_HALF_VALUES_NOT_ALLOWED_PRE = 5,
	eFAIL_INVALID_PRE_VALUE_FOR_NUMBER = 6,
	eFAIL_PREV_USER_PRE_HIGHER_VALUE = 7,
	eFAIL_BLANK_DATA = 8,
	eUNINTIALISED = -1
};

enum class CURRENT_ROMAN_VALUE
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
	bool lastValueI();
	bool lastValueX();
	bool lastValueC();
	bool lastValueM();
	void initValues();
private:
	bool m_bDataValid;
	
	int m_nDecimalValue;

	eStatusCode m_eStatusCode;
	int m_nIvalues; 
	int m_nVvalues;
	int m_nXvalues;
	int m_nLvalues;
	int m_nCvalues;
	int m_nDvalues;
	int m_nMvalues;

	int m_n_5000value; // V with line above counter for 5000 roman numerals we use ^V or ^v
	int m_n_10000value; // X with line above for 10000 roman numerals - we use ^X or ^x

	bool m_bIusedPreValue;
	bool m_bXusedPreValue;
	bool m_bCusedPreValue;

	CURRENT_ROMAN_VALUE lastValue;
};

