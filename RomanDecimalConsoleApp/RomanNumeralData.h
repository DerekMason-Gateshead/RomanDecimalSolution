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
	eUNINTIALISED = -1
};

enum class CURRENT_ROMAN_VALUE
{
	Undef,
	I,
	V,
	X,
	L,
	C,
	D,
	M
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
private:
	bool m_bDataValid = false;
	
	
	int m_nDecimalValue = 0;

	eStatusCode m_eStatusCode = eStatusCode::eUNINTIALISED;
	int m_nIvalues = 0; 
	int m_nVvalues = 0;
	int m_nXvalues = 0;
	int m_nLvalues = 0;
	int m_nCvalues = 0;
	int m_nDvalues = 0;
	int m_nMvalues = 0;



	CURRENT_ROMAN_VALUE lastValue =	CURRENT_ROMAN_VALUE::Undef;
};

