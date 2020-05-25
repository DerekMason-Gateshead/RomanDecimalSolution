#pragma once
#include <string>

struct valuesForTenBase
{
	std::string unit;
	std::string fiveValue;
	std::string tenValue;
};

class DecimalToRoman
{

public:
	// get the romman numeral output is sRomanNumeral from string sDecValue true on success
	bool getRomanNumeral(const std::string& sDecValue, std::string& sRomanNumeral);
	
	// get the romman numeral output is sRomanNumeral from integer nDecimalInput true on success
	bool getRomanNumeral(int nDecimalInput, std::string& sRomanNumeral);
private:
	
	// Build roman numeral outpur from a single decimal value (0 - 9) dependent on base (0 is blank) 
	void getTenBaseValue(std::string& Ouput, int value, const valuesForTenBase& valueSet);

};

