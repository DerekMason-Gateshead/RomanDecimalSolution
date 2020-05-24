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
	int aRomanNumeralCounts[int(RomanIndex::FINAL_INDEX)];  // needs to contain I,V,X,L,C,D,M,5000,10000 counts

	int indexLastValue = -1;
	
	bool hatChar = false; // used superceeded by V or X (for 5000 and 10000)

	initValues();

	for (size_t i = 0; i < (int(RomanIndex::FINAL_INDEX)); i++)
	{
		aRomanNumeralCounts[i] = 0;
	}

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

			m_bDataValid = RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_I,
								ROMAN_I_INCREMENT,  
								0, // No decrement for I as no possible pre values
								indexLastValue, aRomanNumeralCounts, m_eStatusCode);
			
			indexLastValue = (int)RomanIndex::INDEX_I;
			break;
		case ROMAN_V_5:
			if (hatChar)
			{
				hatChar = false;

			    m_bDataValid = RomanNumeralData::handleHalfDecimalInput((int)RomanIndex::INDEX_5000,
					ROMAN_V_HAT_INCREMENT,
					DECREMENT_IF_PREM,
					indexLastValue, aRomanNumeralCounts, m_eStatusCode);

				indexLastValue = (int)RomanIndex::INDEX_5000;
				break;
			}

			m_bDataValid = RomanNumeralData::handleHalfDecimalInput((int)RomanIndex::INDEX_V,
								ROMAN_V_INCREMENT,
								DECREMENT_IF_PREI,
								indexLastValue, aRomanNumeralCounts, m_eStatusCode);

			indexLastValue = (int)RomanIndex::INDEX_V;
			break;

		case ROMAN_X_10:
			
			if (hatChar)
			{
				hatChar = false;

				 m_bDataValid =	RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_10000,
					ROMAN_X_HAT_INCREMENT,
					DECREMENT_IF_PREM,
					indexLastValue, aRomanNumeralCounts, m_eStatusCode);

				indexLastValue = (int)RomanIndex::INDEX_10000;
				break;
			}


			m_bDataValid =	RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_X,
				ROMAN_X_INCREMENT,
				DECREMENT_IF_PREI,
				indexLastValue, aRomanNumeralCounts, m_eStatusCode);

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

		    m_bDataValid =	RomanNumeralData::handleHalfDecimalInput((int)RomanIndex::INDEX_L,
								ROMAN_L_INCREMENT,
								DECREMENT_IF_PREX,
								indexLastValue, aRomanNumeralCounts, m_eStatusCode);
			
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

			m_bDataValid = RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_C,
				ROMAN_C_INCREMENT,
				DECREMENT_IF_PREX,
				indexLastValue, aRomanNumeralCounts, m_eStatusCode);

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

 			m_bDataValid = RomanNumeralData::handleHalfDecimalInput((int)RomanIndex::INDEX_D,
				ROMAN_D_INCREMENT,
				DECREMENT_IF_PREC,
				indexLastValue, aRomanNumeralCounts, m_eStatusCode);

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

			m_bDataValid = RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_M,
				ROMAN_M_INCREMENT,
				DECREMENT_IF_PREC,
				indexLastValue, aRomanNumeralCounts, m_eStatusCode);

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

bool RomanNumeralData::getRomanNumeral(const std::string &sDecValue, std::string& sRomanNumeral)
{
	int value = 0;
	int multiplier = (int) pow(10, (sDecValue.length() - 1));
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



bool RomanNumeralData::getRomanNumeral(int nDecimalInput, std::string& sRomanNumeral)
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


void RomanNumeralData::getTenBaseValue(std::string& Output, int value, const std::string& unit, const std::string& fiveValue, const std::string& tenValue)
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

void RomanNumeralData::initValues()
{
	m_bDataValid = false;

	m_nDecimalValue = 0;

	m_eStatusCode = eStatusCode::eUNINTIALISED;

	
}

// generic method to handle half values
bool RomanNumeralData::handleHalfDecimalInput(int index, 
											int incrementValue,
											int decrementValue,
											int indexLastValue,
											int counters[int(RomanIndex::FINAL_INDEX)],
											eStatusCode &statusCode)
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
				statusCode = eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER;
				return false;
			}
		}
	}

	counters[index]++;

	m_nDecimalValue += incrementValue;

	if (counters[index] > MAX_HALF_ROMAN_NUMERALS)
	{
		statusCode = eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES;
		return false;
	}

	// this stuff is rependent on last value do if last value is index -1 
	if ((index > 0) && (indexLastValue >= 0))
	{
		if ((index - 1) == indexLastValue)
		{
			if (counters[index - 1] > MAX_PRE_BASE_TEN)
			{
				statusCode = eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES;
				return false;
			}
			else
			{
				// need to woek this out
				m_nDecimalValue -= decrementValue;
			}

			counters[index - 1] = COUNT_AFTER_SUBRTACT_VALUE;
		}
	}
	return true;
}

bool RomanNumeralData::handleFullDecimalInput(int index, 
												int incrementValue, 
												int decrementValue, 
												int indexLastValue, 
												int counters[int(RomanIndex::FINAL_INDEX)],
												eStatusCode &statusCode)
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
				statusCode = eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER;
				return false;
			}
		}
	}

	if (index > 0)
	{
		// one index less must be a half value which cannot be pre this
		if (counters[index - 1] > 0)
		{
			statusCode = eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER;
			return false;
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
				statusCode = eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES;
				return false;
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
		statusCode = eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES;
		return false;
	}

	return true;
}


