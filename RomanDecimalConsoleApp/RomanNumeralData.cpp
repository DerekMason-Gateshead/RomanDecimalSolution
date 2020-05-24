#include "RomanNumeralData.h"

#define ROMAN_I_1 'I'
#define ROMAN_V_5 'V'
#define ROMAN_X_10 'X'
#define ROMAN_L_50 'L'
#define ROMAN_C_100 'C'
#define ROMAN_D_500 'D'
#define ROMAN_M_1000 'M'

#define SPECIAL_PRE_MULTIPLIER '^'

#define ROMAN_V_INCREMENT 5
#define ROMAN_X_INCREMENT 10
#define ROMAN_L_INCREMENT 50
#define ROMAN_C_INCREMENT 100
#define ROMAN_D_INCREMENT 500
#define ROMAN_M_INCREMENT 1000
#define ROMAN_V_HAT_INCREMENT 5000

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

			handleRomanNumeral_I();
			
			indexLastValue = (int)RomanIndex::INDEX_I;
			m_nLastRomanNumeral = ROMAN_NUMERAL_VALUE::I;
			break;
		case ROMAN_V_5:
			if (hatChar)
			{
				hatChar = false;

				//handleRomanNumeralfor5000();
				RomanNumeralData::handleHalfDecimalInput((int)RomanIndex::INDEX_5000,
					ROMAN_V_HAT_INCREMENT,
					DECREMENT_IF_PREM,
					indexLastValue, m_RomanNumeralCounts);

				m_nLastRomanNumeral = ROMAN_NUMERAL_VALUE::ROMAN5000;
				indexLastValue = (int)RomanIndex::INDEX_5000;
				break;
			}

//			handleRomanNumeral_V();
			RomanNumeralData::handleHalfDecimalInput((int)RomanIndex::INDEX_V,
				ROMAN_V_INCREMENT,
				DECREMENT_IF_PREI,
				indexLastValue, m_RomanNumeralCounts);

			indexLastValue = (int)RomanIndex::INDEX_V;
			m_nLastRomanNumeral = ROMAN_NUMERAL_VALUE::V;
			break;

		case ROMAN_X_10:
			

			handleRomanNumeral_X();

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

		//	handleRomanNumeral_L();

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

			handleRomanNumeral_C();


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

		//	handleRomanNumeral_D();
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

			handleRomanNumeral_M();
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

// Handles where the last value was I called when I superceeded by V or X 
void RomanNumeralData::lastRomanNumeral_I()
{
//	m_bIusedPreValue = true;
//	enum class RomanIndex
	//	enum class RomanIndex
		
	if (m_RomanNumeralCounts[(int)RomanIndex::INDEX_I] > MAX_PRE_BASE_TEN)
	{	
		m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES;
		m_bDataValid = false;
	}
	else // must be one
	{ 
		m_nDecimalValue -= DECREMENT_IF_PREI;
	}

	// set count to 4 as this is in effect 4 numerals
	m_RomanNumeralCounts[(int)RomanIndex::INDEX_I] = COUNT_AFTER_SUBRTACT_VALUE;
}

void RomanNumeralData::lastRomanNumeral_X()
{
//	m_bXusedPreValue = true;
	if (m_RomanNumeralCounts[(int)RomanIndex::INDEX_X] > MAX_PRE_BASE_TEN)
	{
		m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES;
		m_bDataValid = false;
	}
	else // must be one
	{
		m_nDecimalValue -= DECREMENT_IF_PREX;
	}

	m_RomanNumeralCounts[(int)RomanIndex::INDEX_X] = COUNT_AFTER_SUBRTACT_VALUE;
}

void RomanNumeralData::lastRomanNumeral_C()
{
//	m_bCusedPreValue = true;
	if (m_RomanNumeralCounts[(int)RomanIndex::INDEX_C] > MAX_PRE_BASE_TEN)
	{
		m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES;
		m_bDataValid = false;
	}
	else // must be one
	{
		m_nDecimalValue -= DECREMENT_IF_PREC;
	}
	m_RomanNumeralCounts[(int)RomanIndex::INDEX_C] = COUNT_AFTER_SUBRTACT_VALUE;
}

// To be called when a r5000 or r10000 is preceeded by an M
void RomanNumeralData::lastRomanNumeral_M()
{
//	m_bCusedPreValue = true;
	if (m_RomanNumeralCounts[(int)RomanIndex::INDEX_M] > MAX_PRE_BASE_TEN)
	{
		m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES;
		m_bDataValid = false;
	}
	else // must be one
	{
		m_nDecimalValue -= DECREMENT_IF_PREM;
	}
	m_RomanNumeralCounts[(int)RomanIndex::INDEX_M] = COUNT_AFTER_SUBRTACT_VALUE;
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


// This method handle the input of the roman number I
void RomanNumeralData::handleRomanNumeral_I()
{

	m_nDecimalValue++;
	m_RomanNumeralCounts[(int)RomanIndex::INDEX_I]++;

	// if we have more than 3 values say IIII then
	// we have a fail condition
	if (m_RomanNumeralCounts[(int)RomanIndex::INDEX_I] > MAX_BASE10_VALUES)
	{
		m_bDataValid = false;
		m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES;
	}
	m_nLastRomanNumeral = ROMAN_NUMERAL_VALUE::I;
}


// Handles the receit of the roman 10 (X)
void RomanNumeralData::handleRomanNumeral_X()
{
	// An X should never be preceeded by a V at any point
	if (m_RomanNumeralCounts[(int)RomanIndex::INDEX_V] > 0)
	{
		m_bDataValid = false;
		m_eStatusCode = eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER;
		return;
	}

	m_RomanNumeralCounts[(int)RomanIndex::INDEX_X]++;
	m_nDecimalValue += ROMAN_X_INCREMENT;

	if (m_nLastRomanNumeral == ROMAN_NUMERAL_VALUE::I)
	{
		lastRomanNumeral_I();

		// we should  max this on the preceeding I or setting it back if XXXIX 
		m_RomanNumeralCounts[(int)RomanIndex::INDEX_X] = MAX_BASE10_VALUES;
	}

	// if we have too many base 10 values
	if (m_RomanNumeralCounts[(int)RomanIndex::INDEX_X] > MAX_BASE10_VALUES)
	{
		m_bDataValid = false;
		m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES;
	}

}


// Handles the input of the roman numeral C 100 from stream
void RomanNumeralData::handleRomanNumeral_C()
{
	// The C should not be preceeded with a 1, 5 or 50 
	if ((m_RomanNumeralCounts[(int)RomanIndex::INDEX_V] > 0) 
		|| (m_RomanNumeralCounts[(int)RomanIndex::INDEX_L] > 0)
		|| (m_RomanNumeralCounts[(int)RomanIndex::INDEX_I]))
	{
		m_bDataValid = false;
		m_eStatusCode = eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER;
		return;
	}

	m_RomanNumeralCounts[(int)RomanIndex::INDEX_C]++;
	m_nDecimalValue += ROMAN_C_INCREMENT;


	if (m_nLastRomanNumeral == ROMAN_NUMERAL_VALUE::X)
	{
		lastRomanNumeral_X();
		m_RomanNumeralCounts[(int)RomanIndex::INDEX_C] = MAX_BASE10_VALUES;
	}

	if (m_RomanNumeralCounts[(int)RomanIndex::INDEX_C] > MAX_BASE10_VALUES)
	{
		m_bDataValid = false;
		m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES;
	}

}


// handles roman numeral M 1000
void RomanNumeralData::handleRomanNumeral_M()
{
	// faile condition we should not have I,V,X,D or L prior to an M
	if ((m_RomanNumeralCounts[(int)RomanIndex::INDEX_V] > 0)
		|| (m_RomanNumeralCounts[(int)RomanIndex::INDEX_L] > 0)
		|| (m_RomanNumeralCounts[(int)RomanIndex::INDEX_D] > 0)
		|| (m_RomanNumeralCounts[(int)RomanIndex::INDEX_I] > 0)
		|| (m_RomanNumeralCounts[(int)RomanIndex::INDEX_X] > 0))
	{
		m_bDataValid = false;
		m_eStatusCode = eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER;
		return;
	}
	// increment M and main value by 1000
	m_RomanNumeralCounts[(int)RomanIndex::INDEX_M]++;
	m_nDecimalValue += ROMAN_M_INCREMENT;

	if (m_nLastRomanNumeral == ROMAN_NUMERAL_VALUE::C)
	{ 
		lastRomanNumeral_C();
		m_RomanNumeralCounts[(int)RomanIndex::INDEX_M] = MAX_BASE10_VALUES;
	}

	if (m_RomanNumeralCounts[(int)RomanIndex::INDEX_M] > MAX_BASE10_VALUES)
	{
		m_bDataValid = false;
		m_eStatusCode = eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES;
	}

}


