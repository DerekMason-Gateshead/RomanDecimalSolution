#include "RomanNumeralData.h"

#define ROMAN_I_1 'I'
#define ROMAN_V_5 'V'
#define ROMAN_X_10 'X'
#define ROMAN_L_50 'L'
#define ROMAN_C_100 'C'
#define ROMAN_D_500 'D'
#define ROMAN_M_1000 'M'

#define SPECIAL_PRE_MULTIPLIER '^'

#define ROMAN_I_INCREMENT 1
#define ROMAN_V_INCREMENT 5
#define ROMAN_X_INCREMENT 10
#define ROMAN_L_INCREMENT 50
#define ROMAN_C_INCREMENT 100
#define ROMAN_D_INCREMENT 500
#define ROMAN_M_INCREMENT 1000
#define ROMAN_V_HAT_INCREMENT 5000
#define ROMAN_X_HAT_INCREMENT 10000

#define MAX_BASE10_VALUES 3
#define MAX_PRE_BASE_TEN  1
#define MAX_HALF_ROMAN_NUMERALS 1  // For valuse with five in (i.e. half base 10) we are only allowed a single instance

#define DECREMENT_IF_PREI   2
#define DECREMENT_IF_PREX	20
#define DECREMENT_IF_PREC	200
#define DECREMENT_IF_PREM   2000

#define COUNT_AFTER_SUBRTACT_VALUE 4

RomanNumeralData::RomanNumeralData()
{
	initValues();
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
	int indexLastValue = -1;
	
	bool hatChar = false; // used superceeded by V or X (for 5000 and 10000)

	initValues();

	// assume data is valid to start with
	// we will fail on error
	m_bDataValid = true;

	if (data.length() == 0)
	{
		m_bDataValid = false;
		m_eStatusCode = eStatusCode::eFAIL_BLANK_DATA;
	}
	for (size_t i = 0; i < data.length(); i++)
	{
		if (!m_bDataValid) break;

		switch (toupper(data[i]))
		{
		case SPECIAL_PRE_MULTIPLIER:
			if (hatChar)
			{
				// two together make value invalid
				m_eStatusCode = eStatusCode::eFAIL_INVALID_DATA_VALUE;
				m_bDataValid = false;
				break;
			}

			hatChar = true;
			break;
		
		case ROMAN_I_1:
			if (hatChar)
			{
				// the har char multipler would make the value 1000 but we already have M so we wont allow its use
				m_eStatusCode = eStatusCode::eFAIL_INVALID_DATA_VALUE;
				m_bDataValid = false;
				break;
			}

			RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_I,
				ROMAN_I_INCREMENT,  
				0, // No decrement for I as no possible pre values
				indexLastValue, m_RomanNumeralCounts);
			
			indexLastValue = (int)RomanIndex::INDEX_I;
			m_nLastRomanNumeral = ROMAN_NUMERAL_VALUE::I;
			break;
		case ROMAN_V_5:
			if (hatChar)
			{
				hatChar = false;

				RomanNumeralData::handleHalfDecimalInput((int)RomanIndex::INDEX_5000,
					ROMAN_V_HAT_INCREMENT,
					DECREMENT_IF_PREM,
					indexLastValue, m_RomanNumeralCounts);

				m_nLastRomanNumeral = ROMAN_NUMERAL_VALUE::ROMAN5000;
				indexLastValue = (int)RomanIndex::INDEX_5000;
				break;
			}

			RomanNumeralData::handleHalfDecimalInput((int)RomanIndex::INDEX_V,
				ROMAN_V_INCREMENT,
				DECREMENT_IF_PREI,
				indexLastValue, m_RomanNumeralCounts);

			indexLastValue = (int)RomanIndex::INDEX_V;
			m_nLastRomanNumeral = ROMAN_NUMERAL_VALUE::V;
			break;

		case ROMAN_X_10:
			
			if (hatChar)
			{
				hatChar = false;

				RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_10000,
					ROMAN_X_HAT_INCREMENT,
					DECREMENT_IF_PREM,
					indexLastValue, m_RomanNumeralCounts);

				m_nLastRomanNumeral = ROMAN_NUMERAL_VALUE::ROMAN10000;
				indexLastValue = (int)RomanIndex::INDEX_10000;
				break;
			}


			RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_X,
				ROMAN_X_INCREMENT,
				DECREMENT_IF_PREI,
				indexLastValue, m_RomanNumeralCounts);

			m_nLastRomanNumeral = ROMAN_NUMERAL_VALUE::X;
			indexLastValue = (int)RomanIndex::INDEX_X;
			break;

		case ROMAN_L_50:

			if (hatChar)
			{
				// the har char multipler would make the value 50000 well out of range
				m_eStatusCode = eStatusCode::eFAIL_INVALID_DATA_VALUE;
				m_bDataValid = false;
				break;
			}

			RomanNumeralData::handleHalfDecimalInput((int)RomanIndex::INDEX_L,
				ROMAN_L_INCREMENT,
				DECREMENT_IF_PREX,
				indexLastValue, m_RomanNumeralCounts);
			m_nLastRomanNumeral = ROMAN_NUMERAL_VALUE::L;
			indexLastValue = (int)RomanIndex::INDEX_L;

			break;
		case ROMAN_C_100:
			if (hatChar)
			{
				// the har char multipler would make the value 100000 well out of range
				m_eStatusCode = eStatusCode::eFAIL_INVALID_DATA_VALUE;
				m_bDataValid = false;
				break;
			}

			RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_C,
				ROMAN_C_INCREMENT,
				DECREMENT_IF_PREX,
				indexLastValue, m_RomanNumeralCounts);

			m_nLastRomanNumeral = ROMAN_NUMERAL_VALUE::C;
			indexLastValue = (int)RomanIndex::INDEX_C;

			break;


		case ROMAN_D_500:
			if (hatChar)
			{
				// the har char multipler would make the value 100000 well out of range
				m_eStatusCode = eStatusCode::eFAIL_INVALID_DATA_VALUE;
				m_bDataValid = false;
				break;
			}

			RomanNumeralData::handleHalfDecimalInput((int)RomanIndex::INDEX_D,
				ROMAN_D_INCREMENT,
				DECREMENT_IF_PREC,
				indexLastValue, m_RomanNumeralCounts);

			m_nLastRomanNumeral = ROMAN_NUMERAL_VALUE::D;
			indexLastValue = (int)RomanIndex::INDEX_D;

			break;
		case ROMAN_M_1000:
			if (hatChar)
			{
				// the har char multipler would make the value 100000 well out of range
				m_eStatusCode = eStatusCode::eFAIL_INVALID_DATA_VALUE;
				m_bDataValid = false;
				break;
			}

			RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_M,
				ROMAN_M_INCREMENT,
				DECREMENT_IF_PREC,
				indexLastValue, m_RomanNumeralCounts);

			m_nLastRomanNumeral = ROMAN_NUMERAL_VALUE::M;
			indexLastValue = (int)RomanIndex::INDEX_M;

			break;

		default:
			// Not defined so invalid data
			m_eStatusCode = eStatusCode::eFAIL_INVALID_DATA_VALUE;
			m_bDataValid = false;
			break;
		}
	}


	if (m_bDataValid)
	{
		m_eStatusCode = eStatusCode::eSUCCESS;
	}
	else
	{
		m_nDecimalValue = -1;
	}
}

int RomanNumeralData::romanDecimalValue()
{
	return m_nDecimalValue;
}


void RomanNumeralData::initValues()
{
	m_bDataValid = false;

	m_nDecimalValue = 0;

	m_eStatusCode = eStatusCode::eUNINTIALISED;

	for (size_t i = 0; i < (int (RomanIndex::FINAL_INDEX)); i++)
	{
		m_RomanNumeralCounts[i] = 0;
	}

	m_nLastRomanNumeral = ROMAN_NUMERAL_VALUE::Undef;
}

// generic method to handle half values
void RomanNumeralData::handleHalfDecimalInput(int index, 
											int incrementValue,
											int decrementValue,
											int indexLastValue,
											int counters[int(RomanIndex::FINAL_INDEX)])
{
	#define OFFSET_FOR_INDEX_CHECK_COMPLETE 2
	// we need to check that invalid counters have not been called
	if (index > (int)RomanIndex::INDEX_V)
	{
		// check from 0 to two indexes below current value
		for (size_t i = 0; i <= (index - OFFSET_FOR_INDEX_CHECK_COMPLETE); i++)
		{
			if (counters[i] > 0)
			{
				m_bDataValid = false;
				m_eStatusCode = eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER;
				return;
			}
		}
	}

	counters[index]++;

	m_nDecimalValue += incrementValue;

	if (counters[index] > MAX_HALF_ROMAN_NUMERALS)
	{
		m_bDataValid = false;
		m_eStatusCode = eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES;
		return;
	}
	
	
	// this stuff is rependent on last value do if last value is index -1 
	if ((index > 0) && (indexLastValue >= 0))
	{
		if ((index - 1) == indexLastValue)
		{
			if (m_RomanNumeralCounts[index - 1] > MAX_PRE_BASE_TEN)
			{
				m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES;
				m_bDataValid = false;
			}
			else
			{
				// need to woek this out
				m_nDecimalValue -= decrementValue;
			}

			counters[index - 1] = COUNT_AFTER_SUBRTACT_VALUE;
		}
	}
}

void RomanNumeralData::handleFullDecimalInput(int index, int incrementValue, int decrementValue, int indexLastValue, int counters[int(RomanIndex::FINAL_INDEX)])
{
#define OFFSET_FOR_FULL_INDEX_CHECK_COMPLETE 3
	// we need to check that invalid counters have not been called
	if (index > (int)RomanIndex::INDEX_X)
	{
		// check from 0 to two indexes below current value
		for (size_t i = 0; i <= (index - OFFSET_FOR_FULL_INDEX_CHECK_COMPLETE); i++)
		{
			if (counters[i] > 0)
			{
				m_bDataValid = false;
				m_eStatusCode = eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER;
				return;
			}
		}
	}

	if (index > 0)
	{
		// one index less must be a half value which cannot be pre this
		if (counters[index - 1] > 0)
		{
			m_bDataValid = false;
			m_eStatusCode = eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER;
			return;
		}
	}

	counters[index]++;
	m_nDecimalValue += incrementValue;

	// this stuff is rependent on last value do if last value is index -1 
	if ((index > 1) && (indexLastValue >= 0))
	{
		if ((index - 2) == indexLastValue)
		{
			if (counters[index - 2] > MAX_PRE_BASE_TEN)
			{
				m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES;
				m_bDataValid = false;
				return;
			}
			else
			{
				// need to woek this out
				m_nDecimalValue -= decrementValue;
			}

			counters[index - 2] = COUNT_AFTER_SUBRTACT_VALUE;

			counters[index] = MAX_BASE10_VALUES;

		}
	}

	if (counters[index] > MAX_BASE10_VALUES)
	{
		m_bDataValid = false;
		m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES;
	}
}


