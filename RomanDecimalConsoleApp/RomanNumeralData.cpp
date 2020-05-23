#include "RomanNumeralData.h"

RomanNumeralData::RomanNumeralData()
{
}

RomanNumeralData::~RomanNumeralData()
{
}

bool RomanNumeralData::IsDataValid()
{
	return false;
}

void RomanNumeralData::setRomanNumeralData(std::string& data)
{
	bool dataValid = true;

	for (size_t i = 0; i < data.length; i++)
	{
		switch (data[i])
		{
		default:
			// Not defined so invalid data
			dataValid = false;
			break;
		}
	}

}
