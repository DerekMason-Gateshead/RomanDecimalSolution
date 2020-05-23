#pragma once
#include <string>

enum  eStatusCode
{
	eSUCCESS = 0,
	eFAIL_INVALID_DATA_VALUE = 1,
	eFAIL_TOO_MANY_I_VALUES = 2,
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
private:
	bool m_bDataValid = false;
	int m_nDecimalValue = 0;

	eStatusCode m_eStatusCode = eStatusCode::eUNINTIALISED;
	int m_nIvalues = 0;
};

