#include "RomanNumeralData.h"

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

	

	for (size_t i = 0; i < data.length(); i++)
	{
		switch (data[i])
		{
		case 'I':

			break;
		case 'V':
			break;

		default:
			// Not defined so invalid data
			dataValid = false;
			break;
		}
	}

	m_bDataValid = dataValid;

}
