#include "RomanNumeralData.h"

#define ROMAN_I_1 'I'
#define ROMAN_V_5 'V'

#define ROMAN_V_INCREMENT 5

#define MAX_BASE10_VALUES 3

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

eStatusCode RomanNumeralData::getStatusCode()
{
	return m_eStatusCode;
}

void RomanNumeralData::setRomanNumeralData(const std::string &data)
{
	bool dataValid = true;

	m_nDecimalValue = 0;
	m_nIvalues = 0;

	for (size_t i = 0; i < data.length(); i++)
	{
		switch (data[i])
		{
		case ROMAN_I_1:
			m_nDecimalValue++;
			m_nIvalues++;

			if (m_nIvalues > MAX_BASE10_VALUES)
			{
				dataValid = false;
				m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_I_VALUES;
			}
			break;
		case ROMAN_V_5:
			m_nDecimalValue += ROMAN_V_INCREMENT;
			break;

		default:
			// Not defined so invalid data
			m_eStatusCode = eStatusCode::eFAIL_INVALID_DATA_VALUE;
			dataValid = false;
			break;
		}
	}

	if (dataValid)
	{
		m_eStatusCode = eStatusCode::eSUCCESS;
	}
	else
	{
		m_nDecimalValue = -1;
	}
	

	m_bDataValid = dataValid;

}

int RomanNumeralData::romanDecimalValue()
{
	return m_nDecimalValue;
}
