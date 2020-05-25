#include "DecimalToRoman.h"



// Get romman numeral output from a decimal string - this convert to decimal and call overloaded method
// if not a decimal value in sDecValue then returns false else returns from overload method
bool DecimalToRoman::getRomanNumeral(const std::string& sDecValue, std::string& sRomanNumeral)
{
	int value = 0;
	int multiplier = (int)pow(10, (sDecValue.length() - 1));
	for (size_t i = 0; i < sDecValue.length(); i++)
	{
		if (!(isdigit(sDecValue[i])))
		{
			return false;
		}

		value += multiplier * (sDecValue[i] - '0');
		multiplier /= 10;

	}


	return getRomanNumeral(value, sRomanNumeral);
}


// gets a roman numeral string from an integer input range (1 to 10000)
// returns true if in range else false
bool DecimalToRoman::getRomanNumeral(int nDecimalInput, std::string& sRomanNumeral)
{
	int numberThousands = nDecimalInput / 1000;
	int numberHundreds = (nDecimalInput % 1000) / 100;
	int numberTens = (nDecimalInput % 100) / 10;
	int numberOneUnits(nDecimalInput % 10);

	sRomanNumeral = "";

	if (nDecimalInput > 10000)
	{
		return false;
	}

	if (nDecimalInput < 1)
	{
		return false;
	}

	if (nDecimalInput == 10000)
	{
		sRomanNumeral = "^X";
	}

	if (numberThousands > 0)
	{
		std::string output;

		getTenBaseValue(output, numberThousands, "M", "^V", "^X");
		sRomanNumeral += output;
	}

	if (numberHundreds > 0)
	{
		std::string output;

		getTenBaseValue(output, numberHundreds, "C", "D", "M");
		sRomanNumeral += output;
	}

	if (numberTens > 0)
	{
		std::string output;

		getTenBaseValue(output, numberTens, "X", "L", "C");
		sRomanNumeral += output;
	}

	if (numberOneUnits > 0)
	{
		std::string output;

		getTenBaseValue(output, numberOneUnits, "I", "V", "X");
		sRomanNumeral += output;
	}

	return true;
}



// Gets a ten pase value from the value, the roman output is dependent on the unit, fivevalue and ten value
// i.e. for 10,20,...90 use X for unit L for fivevalue and C for tenValue, note we needed strings for 
// 5000 and 10000
// The string return is set in output
void DecimalToRoman::getTenBaseValue(std::string& Output,
	int value,
	const std::string& unit,
	const std::string& fiveValue,
	const std::string& tenValue)
{
	switch (value)
	{
	case 1:
		Output = unit;
		break;
	case 2:
		Output = unit + unit;
		break;
	case 3:
		Output = unit + unit + unit;
		break;
	case 4:
		Output = unit + fiveValue;
		break;
	case 5:
		Output = fiveValue;
		break;
	case 6:
		Output = fiveValue + unit;

		break;
	case 7:
		Output = fiveValue + unit + unit;
		break;

	case 8:
		Output = fiveValue + unit + unit + unit;
		break;
	case 9:
		Output = unit + tenValue;
		break;

	}
}