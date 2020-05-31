#include "RomanNumeralData.h"
#include <array>

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


#define DECREMENT_IF_PRE_I   2
#define DECREMENT_IF_PRE_X	20
#define DECREMENT_IF_PRE_C	200
#define DECREMENT_IF_PRE_M   2000



// constructor
RomanNumeralData::RomanNumeralData() : 
			numeral_V(
				RomanIndex::INDEX_V,
				ROMAN_V_INCREMENT,
				DECREMENT_IF_PRE_I),
			numeral_L(
				RomanIndex::INDEX_L,
				ROMAN_L_INCREMENT,
				DECREMENT_IF_PRE_X),
			numeral_D(RomanIndex::INDEX_D,
				ROMAN_D_INCREMENT,
				DECREMENT_IF_PRE_C)
{
	for (size_t i = 0; i < 512; i++)
	{
		romanNumerals[i] = nullptr;
	}

	romanNumerals['v'] = &numeral_V;
	romanNumerals['V'] = &numeral_V;
	romanNumerals['l'] = &numeral_L;
	romanNumerals['L'] = &numeral_L;
	romanNumerals['d'] = &numeral_D;
	romanNumerals['D'] = &numeral_D;

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
	





	HalfRomanNumeral numeral_5000(RomanIndex::INDEX_5000,
		ROMAN_V_HAT_INCREMENT,
		DECREMENT_IF_PRE_M);

	FullRomanNumeral numeral_I(RomanIndex::INDEX_I,
		ROMAN_I_INCREMENT, 0);


	FullRomanNumeral numeral_X(RomanIndex::INDEX_X,
									ROMAN_X_INCREMENT, DECREMENT_IF_PRE_I);

	FullRomanNumeral numeral_C(RomanIndex::INDEX_C,
		ROMAN_C_INCREMENT, DECREMENT_IF_PRE_X);

	FullRomanNumeral numeral_M(RomanIndex::INDEX_M,
		ROMAN_M_INCREMENT, DECREMENT_IF_PRE_C);

	FullRomanNumeral numeral_10000(RomanIndex::INDEX_10000,
									ROMAN_X_HAT_INCREMENT,
									DECREMENT_IF_PRE_M);

	
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

		RomanNumeral* pRomanNumeral = romanNumerals[sRomanNumeral[i]]; //  != nullptr)
		
		if ((pRomanNumeral != nullptr) && (!hatChar))
		{
			pRomanNumeral->HandleInput(m_romanNumeralDataForInput, localInputData);
			continue;
		}
		

		switch (toupper(sRomanNumeral[i]))
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

			numeral_I.HandleInput(m_romanNumeralDataForInput, localInputData);
			break;
		case ROMAN_V_5:
			if (hatChar)
			{
				hatChar = false;

				numeral_5000.HandleInput(m_romanNumeralDataForInput, localInputData);
				break;
			}

		//	numeral_V.HandleInput(m_romanNumeralDataForInput, localInputData);
			break;

		case ROMAN_X_10:
			
			if (hatChar)
			{
				hatChar = false;

				numeral_10000.HandleInput(m_romanNumeralDataForInput, localInputData);
				break;
			}

			numeral_X.HandleInput(m_romanNumeralDataForInput, localInputData);
			break;

		case ROMAN_L_50:

			if (hatChar)
			{
				// the har char multipler would make the value 50000 well out of range
				m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_INVALID_DATA_VALUE);
				break;
			}

		//	numeral_L.HandleInput(m_romanNumeralDataForInput, localInputData);
			break;
		case ROMAN_C_100:
			if (hatChar)
			{
				// the har char multipler would make the value 100000 well out of range
				m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_INVALID_DATA_VALUE);
				break;
			}

			numeral_C.HandleInput(m_romanNumeralDataForInput, localInputData);
			break;


		case ROMAN_D_500:
			if (hatChar)
			{
				// the har char multipler would make the value 100000 well out of range
				m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_INVALID_DATA_VALUE);
				break;
			}

			numeral_D.HandleInput(m_romanNumeralDataForInput, localInputData);
			break;
		case ROMAN_M_1000:
			if (hatChar)
			{
				// the har char multipler would make the value 100000 well out of range
				m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_INVALID_DATA_VALUE);
				break;
			}

			numeral_M.HandleInput(m_romanNumeralDataForInput, localInputData);

			break;

		default:
			// Not defined so invalid data
			m_romanNumeralDataForInput.setError(eStatusCode::eFAIL_INVALID_DATA_VALUE);
			break;
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

