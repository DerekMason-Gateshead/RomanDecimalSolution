#pragma once
#include <string>

class RomanNumeralData
{
	
public:
	RomanNumeralData();
	virtual ~RomanNumeralData();

	bool IsDataValid();

	void setRomanNumeralData(const std::string &data);
private:
	bool m_bDataValid = false;
};

