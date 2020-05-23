#pragma once
#include <string>

class RomanNumeralData
{
	
public:
	RomanNumeralData();
	virtual ~RomanNumeralData();

	bool IsDataValid();

	void setRomanNumeralData(std::string& data);

};

