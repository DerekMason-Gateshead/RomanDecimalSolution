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

// constructor
RomanNumeralData::RomanNumeralData()
{
	initValues();
}

// destructor
RomanNumeralData::~RomanNumeralData()
{
}

//  returns true if the parsed roman numeral data is good
bool RomanNumeralData::IsDataValid()
{
	return m_romanNumeralDataForInput.valid;
}

// returns status code of data parsing on roman numeral input string
eStatusCode RomanNumeralData::getStatusCode()
{
	return m_romanNumeralDataForInput.statusCode;
}

// setRomanNumeralData - this takes in the data and sets up the decimal value of the roman numeral from it
// checking the data has valid data, the effected members are m_sSTatusCode, m_bDataValid and m_nDecimal in methods called
void RomanNumeralData::setRomanNumeralData(const std::string &data)
{

	int indexLastValue = -1;
	
	bool hatChar = false; // used superceeded by V or X (for 5000 and 10000)

	initValues();

	localDataForRomanNumeralInput localInputData;

	localInputData.Init();


	// assume data is valid to start with
	// we will fail on error
	m_romanNumeralDataForInput.valid = true;

	if (data.length() == 0)
	{
		m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_BLANK_DATA);
	}

	for (size_t i = 0; i < data.length(); i++)
	{
		if (!m_romanNumeralDataForInput.valid) break;

		switch (toupper(data[i]))
		{
		case SPECIAL_PRE_MULTIPLIER:
			if (hatChar)
			{
				// two together make value invalid
				m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_INVALID_DATA_VALUE);
				break;
			}
			hatChar = true;
			break;
		
		case ROMAN_I_1:
			if (hatChar)
			{
				
				// the har char multipler would make the value 1000 but we already have M so we wont allow its use
				m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_INVALID_DATA_VALUE);
				break;
			}

			RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_I,
								ROMAN_I_INCREMENT,  
								0, // No decrement for I as no possible pre values
								m_romanNumeralDataForInput, localInputData);
			
			indexLastValue = (int)RomanIndex::INDEX_I;
			break;
		case ROMAN_V_5:
			if (hatChar)
			{
				hatChar = false;

			    RomanNumeralData::handleHalfDecimalInput((int)RomanIndex::INDEX_5000,
					ROMAN_V_HAT_INCREMENT,
					DECREMENT_IF_PREM,
					m_romanNumeralDataForInput, localInputData);

				indexLastValue = (int)RomanIndex::INDEX_5000;
				break;
			}

			RomanNumeralData::handleHalfDecimalInput((int)RomanIndex::INDEX_V,
								ROMAN_V_INCREMENT,
								DECREMENT_IF_PREI,
								m_romanNumeralDataForInput, localInputData);

			indexLastValue = (int)RomanIndex::INDEX_V;
			break;

		case ROMAN_X_10:
			
			if (hatChar)
			{
				hatChar = false;

				RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_10000,
					ROMAN_X_HAT_INCREMENT,
					DECREMENT_IF_PREM,
					 m_romanNumeralDataForInput, localInputData);


				indexLastValue = (int)RomanIndex::INDEX_10000;
				break;
			}


			RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_X,
				ROMAN_X_INCREMENT,
				DECREMENT_IF_PREI,
				m_romanNumeralDataForInput, localInputData);

			indexLastValue = (int)RomanIndex::INDEX_X;
			break;

		case ROMAN_L_50:

			if (hatChar)
			{
				// the har char multipler would make the value 50000 well out of range
				m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_INVALID_DATA_VALUE);
				break;
			}

		    RomanNumeralData::handleHalfDecimalInput((int)RomanIndex::INDEX_L,
								ROMAN_L_INCREMENT,
								DECREMENT_IF_PREX,
								m_romanNumeralDataForInput, localInputData);

			
			indexLastValue = (int)RomanIndex::INDEX_L;

			break;
		case ROMAN_C_100:
			if (hatChar)
			{
				// the har char multipler would make the value 100000 well out of range
				m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_INVALID_DATA_VALUE);
				break;
			}

			RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_C,
				ROMAN_C_INCREMENT,
				DECREMENT_IF_PREX,
				m_romanNumeralDataForInput, localInputData);

			indexLastValue = (int)RomanIndex::INDEX_C;

			break;


		case ROMAN_D_500:
			if (hatChar)
			{
				// the har char multipler would make the value 100000 well out of range
				m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_INVALID_DATA_VALUE);
				break;
			}

 			RomanNumeralData::handleHalfDecimalInput((int)RomanIndex::INDEX_D,
				ROMAN_D_INCREMENT,
				DECREMENT_IF_PREC,
				m_romanNumeralDataForInput, localInputData);

			indexLastValue = (int)RomanIndex::INDEX_D;

			break;
		case ROMAN_M_1000:
			if (hatChar)
			{
				// the har char multipler would make the value 100000 well out of range
				m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_INVALID_DATA_VALUE);
				break;
			}

			RomanNumeralData::handleFullDecimalInput((int)RomanIndex::INDEX_M,
				ROMAN_M_INCREMENT,
				DECREMENT_IF_PREC,
				m_romanNumeralDataForInput, localInputData);

			indexLastValue = (int)RomanIndex::INDEX_M;

			break;

		default:
			// Not defined so invalid data
			m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_INVALID_DATA_VALUE);
			break;
		}
		localInputData.indexLastValue = indexLastValue;

	}


	if (m_romanNumeralDataForInput.valid)
	{
		if (m_romanNumeralDataForInput.decimalValue > 10000)
		{
			m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_RANGE_ERROR);
		}
	}

	if (m_romanNumeralDataForInput.valid)
	{
		m_romanNumeralDataForInput.statusCode  = eStatusCode::eSUCCESS;
	}
	else
	{
		m_romanNumeralDataForInput.decimalValue = -1;
	}
}

// returns the value set up from the roman numeral data passed in setRomanNumeral
int RomanNumeralData::romanDecimalValue()
{
	return m_romanNumeralDataForInput.decimalValue;
}




// initalise values when converting roman to decimal
void RomanNumeralData::initValues()
{
	m_romanNumeralDataForInput.Init();
}

// generic method to handle half values
// index is the index into the counters for the specic unit to evaluate 
// increment value is the value to add to the member decimalvalue
// decrementvalue is the value to decrement the decimal value if preceded by the approriate value (i.e for V then I)
// indexLastValue is an index for the last value prior to this (note -1 indicates this is first value) this is
//				   used to determine if we need to decrement (i.e if one less than index
//  counters reference to an ammendable set of counters - if values of a lower value proceeded this and they are
//                                                        not allowed we can determine an error
//  statusCode allows us to give limited info on the reason for an error
//  return is true if we have no problems with the data else it is false
void RomanNumeralData::handleHalfDecimalInput(int index, 
											int incrementValue,
											int decrementValue,
											dataForRomanNumeralInput& dataRomanNumeralString,
											localDataForRomanNumeralInput& localInputData)
{
	#define OFFSET_FOR_INDEX_CHECK_COMPLETE 2
	// we need to check that invalid counters have not been called
	if (index > (int)RomanIndex::INDEX_V)
	{
		// check from 0 to two indexes below current value
		for (size_t i = 0; i <= (index - OFFSET_FOR_INDEX_CHECK_COMPLETE); i++)
		{
			if (localInputData.counters[i] > 0)
			{
				dataRomanNumeralString.setError(eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER);
				return;
			}
		}
	}

	localInputData.counters[index]++;

	dataRomanNumeralString.decimalValue	+= incrementValue;

	if (localInputData.counters[index] > MAX_HALF_ROMAN_NUMERALS)
	{
		dataRomanNumeralString.setError(eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES);
		return;
	}

	// this stuff is rependent on last value do if last value is index -1 
	if ((index > 0) && (localInputData.indexLastValue >= 0))
	{
		if ((index - 1) == localInputData.indexLastValue)
		{
			if (localInputData.counters[index - 1] > MAX_PRE_BASE_TEN)
			{
				dataRomanNumeralString.setError(eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES);
			}
			else
			{
				// need to woek this out
				dataRomanNumeralString.decimalValue -= decrementValue;
			}

			localInputData.counters[index - 1] = COUNT_AFTER_SUBRTACT_VALUE;
		}
	}
}

// this handles all unit and 10 x unit data
// index is the index into the counters for the specic unit to evaluate 
// increment value is the value to add to the member decimalvalue
// decrementvalue is the value to decrement the decimal value if preceded by the approriate value (i.e for C then X)
// indexLastValue is an index for the last value prior to this (note -1 indicates this is first value) this is
//				   used to determine if we need to decrement i.e if 2 less than index
//  counters reference to an ammendable set of counters - if values of a lower value proceeded this and they are
//                                                        not allowe we can determine an error
//  statusCode allows us to give limited info on the reason for an error
//  return is true if we have no problems with the data else it is false
void RomanNumeralData::handleFullDecimalInput(int index, 
												int incrementValue, 
												int decrementValue,
												dataForRomanNumeralInput& dataRomanNumeralString,
												localDataForRomanNumeralInput& localInputData)
{
#define OFFSET_FOR_FULL_INDEX_CHECK_COMPLETE 3
	// we need to check that invalid counters have not been called
	if (index > (int)RomanIndex::INDEX_X)
	{
		// check from 0 to two indexes below current value
		for (size_t i = 0; i <= (index - OFFSET_FOR_FULL_INDEX_CHECK_COMPLETE); i++)
		{
			if (localInputData.counters[i] > 0)
			{
				dataRomanNumeralString.setError(eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER);
				return;
			}
		}
	}

	if (index > 0)
	{
		// one index less must be a half value which cannot be pre this
		if (localInputData.counters[index - 1] > 0)
		{
			dataRomanNumeralString.setError(eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER);
			return;
		}
	}
	localInputData.counters[index]++;

	dataRomanNumeralString.decimalValue  += incrementValue;

	// this stuff is rependent on last value do if last value is index -1 
	if ((index > 1) && (localInputData.indexLastValue >= 0))
	{
		if ((index - 2) == localInputData.indexLastValue)
		{
			if (localInputData.counters[index - 2] > MAX_PRE_BASE_TEN)
			{
				dataRomanNumeralString.setError(eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES);
				return;
			}
			else
			{
				// need to woek this out
				dataRomanNumeralString.decimalValue -= decrementValue;
			}

			localInputData.counters[index - 2] = COUNT_AFTER_SUBRTACT_VALUE;

			localInputData.counters[index] = MAX_BASE10_VALUES;

		}
	}

	if (localInputData.counters[index] > MAX_BASE10_VALUES)
	{
		dataRomanNumeralString.setError(eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES);
	}
}


