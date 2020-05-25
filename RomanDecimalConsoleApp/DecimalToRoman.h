#pragma once
#include <string>

class DecimalToRoman
{
public:
	bool getRomanNumeral(const std::string& sDecValue, std::string& sRomanNumeral);
	bool getRomanNumeral(int nDecimalInput, std::string& sRomanNumeral);
private:
	void getTenBaseValue(std::string& Ouput, int value, const std::string& unit, const std::string& fiveValue, const std::string& tenValue);

};

