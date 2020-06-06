#pragma once

#define MAX_BASE10_VALUES 3
#define MAX_PRE_BASE_TEN  1
#define MAX_HALF_ROMAN_NUMERALS 1  // For valuse with five in (i.e. half base 10) we are only allowed a single instance
#define COUNT_AFTER_SUBRTACT_VALUE 4

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


// Base class for an individual roman numeral
class RomanNumeral
{
public:
	RomanNumeral(RomanIndex Index, int incrementValue, int decrementValue);
	virtual ~RomanNumeral();

	bool IsHalfValue();
	
protected:
	 
	int count = 0;
// decrementvalue is the value to decrement the decimal value if preceded by the approriate value (i.e for C then X)

	// index is the index into the Roman Numeral set up for (used for handling counter info)
	RomanIndex indexOfRomanNumeral;

	// increment value is has the value to add to value for this number
	int incrementValue;

	// decrementvalue is the value to decrement the value if preceded by the approriate value (i.e for C then X)
	int decrementValue;


public:

	
	int getCount() { return count; }
	int getIncrementValue() { return incrementValue; }
	int getDecrementValue() { return decrementValue;  }

	RomanIndex getIndex() { return indexOfRomanNumeral; }
};

