#include "RomanNumeralData.h"

#define ROMAN_I_1 'I'
#define ROMAN_V_5 'V'


RomanNumeralData::RomanNumeralData()
{
}

RomanNumeralData::~RomanNumeralData()
{
}

bool RomanNumeralData::IsDataValid()
{
	return m_bDataValid;
}

void RomanNumeralData::setRomanNumeralData(const std::string &data)
{
	bool dataValid = true;

	m_nDecimalValue = 0;

	for (size_t i = 0; i < data.length(); i++)
	{
		switch (data[i])
		{
		case ROMAN_I_1:
			m_nDecimalValue++;
			break;
		case ROMAN_V_5:
			m_nDecimalValue += 5;
			break;

		default:
			// Not defined so invalid data
			dataValid = false;
			break;
		}
	}

	m_bDataValid = dataValid;

}

int RomanNumeralData::romanDecimalValue()
{
	return m_nDecimalValue;
}
