#include "RomanNumeralData.h"

#define ROMAN_I_1 'I'
#define ROMAN_V_5 'V'

#define ROMAN_V_INCREMENT 5

#define MAX_BASE10_VALUES 3
#define MAX_PRE_BASE_TEN  1
#define MAX_PRE_HALF_BASE_TEN 1
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
	m_nVvalues = 0;

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
				m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES;
			}
			lastValue = CURRENT_ROMAN_VALUE::I;
			break;
		case ROMAN_V_5:
			m_nVvalues++;
			m_nDecimalValue += ROMAN_V_INCREMENT;

			if (m_nVvalues > MAX_PRE_HALF_BASE_TEN)
			{
				dataValid = false;
				m_eStatusCode = eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES;
			}

			switch (lastValue)
			{
			case CURRENT_ROMAN_VALUE::I:
				if (m_nIvalues > MAX_PRE_BASE_TEN)
				{
					dataValid = false;
					m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES;
				}
				else // must be one
				{
					m_nDecimalValue -= 2;
				}
				break;
			default:
				break;
			}

			lastValue = CURRENT_ROMAN_VALUE::V;
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
