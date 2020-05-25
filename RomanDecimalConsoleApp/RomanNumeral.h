#pragma once

enum class RomanIndex
{
	INDEX_I = 0,
	INDEX_V = 1,
	INDEX_X = 2,
	INDEX_L = 3,
	INDEX_C = 4,
	INDEX_D = 5,
	INDEX_M = 6,
	INDEX_5000 = 7,
	INDEX_10000 = 8,

	FINAL_INDEX = 9 // Last Index increment if we add more values
};

// use to store limited status information on parsing of roman numeral
enum  class eStatusCode
{
	eSUCCESS = 0,
	eFAIL_INVALID_DATA_VALUE = 1,
	eFAIL_TOO_MANY_BASE10_VALUES = 2,
	eFAIL_TOO_MANY_PRE_BASE_10_VALUES = 3,
	eFAIL_TOO_MANT_HALF_TEN_VALUES = 4,
	eFAIL_INVALID_PRE_VALUE_FOR_NUMBER = 5,
	eFAIL_PREV_USER_PRE_HIGHER_VALUE = 6,
	eFAIL_BLANK_DATA = 7,
	eFAIL_RANGE_ERROR = 8,
	eUNINTIALISED = -1
};


struct SetupRomanNumeral
{
	// Index to RomanNumeral
	int index; // IndexToRomanNumeral 
	int incrementValue;
	int decrementValue;
	
};

//  Structure containing fixed data for roman numeral input
// this is whether it is valid, the decimal value and error status info
struct dataForRomanNumeralInput
{
	bool valid; // is the input data valid
	int decimalValue; // decimal value calculated from input
	eStatusCode statusCode;  // status Code of data

	void Init()
	{
		valid = false;
		decimalValue = 0;
		statusCode = eStatusCode::eUNINTIALISED;
	}

	void setError(eStatusCode code)
	{
		valid = false;
		statusCode = code;
	}
};

// contains counters for eacj roman numeral and index of last value
struct localDataForRomanNumeralInput
{
	int indexLastValue; // index of previous input value

	// contains I,V,X,L,C,D,M,5000,10000 counts
	int counters[(int)RomanIndex::FINAL_INDEX]; // running counters for each differen numeral
	
	void Init()
	{
		indexLastValue = -1;
		for (int i = 0; i < (int)RomanIndex::FINAL_INDEX; i++)
		{
			counters[i] = 0;
		}
	}
};

// Base class for an individual roman numeral
class RomanNumeral
{
public:
	RomanNumeral(SetupRomanNumeral setupData);
	virtual ~RomanNumeral();


	// will store value of data 1,5,10, etc
	virtual void HandleInput(dataForRomanNumeralInput &dataRomanNumeralString, 
								localDataForRomanNumeralInput &localInputData) = 0;
	

};

