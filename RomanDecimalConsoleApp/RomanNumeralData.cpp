#include "RomanNumeralData.h"
#include <array>

enum class ROMAN_NUM_ASCII_VALUES
{
	UPPER_I = 'I',
	LOWER_I = 'i',
	UPPER_V = 'V',
	LOWER_V = 'v',
	UPPER_X = 'X',
	LOWER_X = 'x',
	UPPER_L = 'L',
	LOWER_L = 'l',
	UPPER_C = 'C',
	LOWER_C = 'c',
	UPPER_D = 'D',
	LOWER_D = 'd',
	UPPER_M = 'M',
	LOWER_M = 'm',
	UPPER_5000 = ('V' + 256),
	LOWER_5000 = ('v' + 256),
	UPPER_10000 = ('X' + 256),
	LOWER_10000 = ('x' + 256)
};


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


#define DECREMENT_IF_PRE_I   2
#define DECREMENT_IF_PRE_X	20
#define DECREMENT_IF_PRE_C	200
#define DECREMENT_IF_PRE_M   2000



// constructor
RomanNumeralData::RomanNumeralData() :
			numeral_I(
				RomanIndex::INDEX_I,
				ROMAN_I_INCREMENT,
				0),
			numeral_V(
				RomanIndex::INDEX_V,
				ROMAN_V_INCREMENT,
				DECREMENT_IF_PRE_I),
			numeral_X(
				RomanIndex::INDEX_X,
				ROMAN_X_INCREMENT, 
				DECREMENT_IF_PRE_I),
			numeral_L(
				RomanIndex::INDEX_L,
				ROMAN_L_INCREMENT,
				DECREMENT_IF_PRE_X),
			numeral_C(
				RomanIndex::INDEX_C,
				ROMAN_C_INCREMENT, 
				DECREMENT_IF_PRE_X),
			numeral_D(RomanIndex::INDEX_D,
				ROMAN_D_INCREMENT,
				DECREMENT_IF_PRE_C),
			numeral_M(
				RomanIndex::INDEX_M,
				ROMAN_M_INCREMENT, 
				DECREMENT_IF_PRE_C),
			numeral_5000(
				RomanIndex::INDEX_5000,
				ROMAN_V_HAT_INCREMENT,
				DECREMENT_IF_PRE_M),
			numeral_10000(
				RomanIndex::INDEX_10000,
				ROMAN_X_HAT_INCREMENT,
				DECREMENT_IF_PRE_M)
{
	for (size_t i = 0; i < 512; i++)
	{
		ArrayOfPointersToRomanNumeralClasses[i] = nullptr;
	}

	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::UPPER_I] = &numeral_I;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::LOWER_I] = &numeral_I;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::UPPER_V] = &numeral_V;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::LOWER_V] = &numeral_V;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::UPPER_X] = &numeral_X;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::LOWER_X] = &numeral_X;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::UPPER_L] = &numeral_L;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::LOWER_L] = &numeral_L;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::UPPER_C] = &numeral_C;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::LOWER_C] = &numeral_C;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::UPPER_D] = &numeral_D;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::LOWER_D] = &numeral_D;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::UPPER_M] = &numeral_M;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::LOWER_M] = &numeral_M;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::UPPER_5000] = &numeral_5000;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::LOWER_5000] = &numeral_5000;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::UPPER_10000] = &numeral_10000;
	ArrayOfPointersToRomanNumeralClasses[(int)ROMAN_NUM_ASCII_VALUES::LOWER_10000] = &numeral_10000;


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

// setRomanNumeralData - this takes in the data in string sRomanNumeral
// and sets up the decimal value of the roman numeral from it checking the 
// data has valid data, the data in m_romanNumeralDataForInput is updated
void RomanNumeralData::setRomanNumeralData(const std::string &sRomanNumeral)
{
	bool hatChar = false; // used superceeded by V or X (for 5000 and 10000)

	initValues();

	localDataForRomanNumeralInput localInputData;

	localInputData.Init();

	// assume data is valid to start with
	// we will fail on error
	m_romanNumeralDataForInput.valid = true;

	if (sRomanNumeral.length() == 0)
	{
		m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_BLANK_DATA);
	}

	for (size_t i = 0; i < sRomanNumeral.length(); i++)
	{
		if (!m_romanNumeralDataForInput.valid) break;

		if (sRomanNumeral[i] == SPECIAL_PRE_MULTIPLIER)
		{
			if (!hatChar)
			{
				hatChar = true;
			}
			else
			{
				m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_INVALID_DATA_VALUE);

			}
			continue;
		}

		RomanNumeral* pRomanNumeral;
		
		if (!hatChar)
		{
			pRomanNumeral = ArrayOfPointersToRomanNumeralClasses[sRomanNumeral[i]];
		}
		else
		{
			pRomanNumeral = ArrayOfPointersToRomanNumeralClasses[sRomanNumeral[i] + 256];
			hatChar = false;
		}

		if (pRomanNumeral != nullptr)
		{
			pRomanNumeral->HandleInput(m_romanNumeralDataForInput, localInputData);
		}
		else
		{
			m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_INVALID_DATA_VALUE);
		}
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

