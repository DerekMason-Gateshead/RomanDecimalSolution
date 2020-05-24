#pragma once
#include <string>

enum  eStatusCode
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
	void lastRomanNumeral_I(); // called when a V or X is preceeded by an I
	void lastRomanNumeral_X();
	void lastRomanNumeral_C();
	void lastRomanNumeral_M();
	void initValues();


	void handleRomanNumeral_I();  // Handles the receit of roman 1 
	void handleRomanNumeral_V();  // Handles the receit of V roman 5
	void handleRomanNumeralfor5000(); // Handles the receit of roman 5000 (we use ^v or ^V
	void handleRomanNumeral_X(); // Handles the receit of roman number 10 (X)
	void handleRomanNumeral_L(); // handles roman numeral 50 L
	void handleRomanNumeral_C(); // handle roman numeral 100 C
	void handleRomanNumeral_D(); // handle roman numeral D 500
	void handleRomanNumeral_M(); // handle roman numeral M 1000

private:
	bool m_bDataValid;
	
	int m_nDecimalValue;

	eStatusCode m_eStatusCode;
	int m_nCountRomanNumeral_I_inInput; // to store number of roman numeral I (1) in string
	int m_nCountRomanNumeral_V_inInput; // to store number of roman numeral V (5) in string
	int m_nCountRomanNumeral_X_inInput; 
	int m_nCountRomanNumeral_L_inInput;
	int m_nCountRomanNumeral_C_inInput;
	int m_nCountRomanNumeral_D_inInput;
	int m_nCountRomanNumeral_M_inInput;

	int m_nCountRomanNumeral5000inInput; // V with line above counter for 5000 roman numerals we use ^V or ^v
	int m_nCountRomanNumeral_10000inInput; // X with line above for 10000 roman numerals - we use ^X or ^x

	bool m_bIusedPreValue;
	bool m_bXusedPreValue;
	bool m_bCusedPreValue;

	ROMAN_NUMERAL_VALUE m_nLastRomanNumeral;
};

