#include "RomanNumeralData.h"

#define ROMAN_I_1 'I'
#define ROMAN_V_5 'V'
#define ROMAN_X_10 'X'
#define ROMAN_L_50 'L'
#define ROMAN_C_100 'C'
#define ROMAN_D_500 'D'
#define ROMAN_M_1000 'M'

#define ROMAN_V_INCREMENT 5
#define ROMAN_X_INCREMENT 10
#define ROMAN_L_INCREMENT 50
#define ROMAN_C_INCREMENT 100
#define ROMAN_D_INCREMENT 500
#define ROMAN_M_INCREMENT 1000

#define MAX_BASE10_VALUES 3
#define MAX_PRE_BASE_TEN  1
#define MAX_PRE_HALF_BASE_TEN 1

#define DECREMENT_IF_PREI   2
#define DECREMENT_IF_PREX	20
#define DECREMENT_IF_PREC	200

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
	m_nXvalues = 0;
	m_nLvalues = 0;
	m_nCvalues = 0;
	m_nDvalues = 0;
	m_nMvalues = 0;

	for (size_t i = 0; i < data.length(); i++)
	{
		if (!dataValid) break;

		switch (toupper(data[i]))
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
				dataValid = lastValueI();

				
				break;
			default:
				break;
			}

			lastValue = CURRENT_ROMAN_VALUE::V;
			break;

		case ROMAN_X_10:
			m_nXvalues++;
			m_nDecimalValue += ROMAN_X_INCREMENT;
			switch (lastValue)
			{
			
			case CURRENT_ROMAN_VALUE::V:
				dataValid = false;
				m_eStatusCode = eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE;
				break;

			case CURRENT_ROMAN_VALUE::I:
				dataValid = lastValueI();
				m_nXvalues = MAX_BASE10_VALUES; // we should be maxed out on these values now
				break;
			default:
				break;
			}

			if (m_nXvalues > MAX_BASE10_VALUES)
			{
				dataValid = false;
				m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES;
			}
			lastValue = CURRENT_ROMAN_VALUE::X;

			break;

		case ROMAN_L_50:
			m_nLvalues++;
			m_nDecimalValue += ROMAN_L_INCREMENT;

			if (m_nLvalues > MAX_PRE_HALF_BASE_TEN)
			{
				dataValid = false;
				m_eStatusCode = eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES;
			}

			switch (lastValue)
			{
			case CURRENT_ROMAN_VALUE::I:
				dataValid = false;
				m_eStatusCode = eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER;

				break;
			case CURRENT_ROMAN_VALUE::V:
				dataValid = false;
				m_eStatusCode = eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE;
				break;
			case CURRENT_ROMAN_VALUE::X:
				dataValid = lastValueX();
				break;
			default:
				break;
			}

			lastValue = CURRENT_ROMAN_VALUE::L;

			break;
		case ROMAN_C_100:
			m_nCvalues++;
			m_nDecimalValue += ROMAN_C_INCREMENT;


			switch (lastValue)
			{
			case CURRENT_ROMAN_VALUE::L:
			case CURRENT_ROMAN_VALUE::V:
				dataValid = false;
				m_eStatusCode = eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE;
				break;

			case CURRENT_ROMAN_VALUE::I:
				dataValid = false;
				m_eStatusCode = eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER;

				break;
			case CURRENT_ROMAN_VALUE::X:
				dataValid = lastValueX();
				m_nCvalues = MAX_BASE10_VALUES;
				break;
			default:
				break;
			}


			if (m_nCvalues > MAX_BASE10_VALUES)
			{
				dataValid = false;
				m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES;
			}

			lastValue = CURRENT_ROMAN_VALUE::C;
			break;


		case ROMAN_D_500:
		case ROMAN_M_1000:
			// TODO
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

bool RomanNumeralData::lastValueI()
{
	if (m_nIvalues > MAX_PRE_BASE_TEN)
	{	
		m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES;
		return false;
	}
	else // must be one
	{
		m_nDecimalValue -= DECREMENT_IF_PREI;
		return true;
	}
}

bool RomanNumeralData::lastValueX()
{
	if (m_nXvalues > MAX_PRE_BASE_TEN)
	{
		m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES;
		return false;
	}
	else // must be one
	{
		m_nDecimalValue -= DECREMENT_IF_PREX;
		return true;
	}
}

