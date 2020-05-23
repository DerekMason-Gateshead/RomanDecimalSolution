#pragma once
#include <string>

class RomanNumeralData
{
	
public:
	RomanNumeralData();
	virtual ~RomanNumeralData();

	bool IsDataValid();

	void setRomanNumeralData(const std::string &data);
	int romanDecimalValue();
private:
	bool m_bDataValid = false;
	int m_nDecimalValue = 0;
};

