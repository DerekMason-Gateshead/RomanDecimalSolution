#include "HalfRomanNumeral.h"


// this handles all half units, i.e 5, 50, 500 etc
// this effects data in dataRomanNumeralString and localInputData
// dataRomanNumeralString has it decimal value updates and if an error the status info
// localInputData - the counter for this index and the last index are updated, other counter 
//  info is used for error checking, lastIndex is used to check for pre roman numerals
void HalfRomanNumeral::HandleInput(dataForRomanNumeralInput& dataRomanNumeralString, localDataForRomanNumeralInput& localInputData)
{
#define OFFSET_FOR_INDEX_CHECK_COMPLETE 2
	// we need to check that invalid counters have not been called
	if ((int) indexOfRomanNumeral > (int)RomanIndex::INDEX_V)
	{
		// check from 0 to two indexes below current value
		for (size_t i = 0; i <= ((int) indexOfRomanNumeral - OFFSET_FOR_INDEX_CHECK_COMPLETE); i++)
		{
			if (localInputData.counters[i] > 0)
			{
				dataRomanNumeralString.setError(eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER);
				return;
			}
		}
	}

	localInputData.counters[(int) indexOfRomanNumeral]++;
	dataRomanNumeralString.decimalValue += incrementValue;

	// we should never have more than one instance of a half value
	if (localInputData.counters[(int) indexOfRomanNumeral] > MAX_HALF_ROMAN_NUMERALS)
	{
		dataRomanNumeralString.setError(eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES);
		return;
	}

	// this stuff is rependent on last value do if last value is index -1 
	if (((int) indexOfRomanNumeral > 0) && (localInputData.indexLastValue >= 0))
	{
		if (((int) indexOfRomanNumeral - 1) == localInputData.indexLastValue)
		{
			if (localInputData.counters[(int) indexOfRomanNumeral - 1] > MAX_PRE_BASE_TEN)
			{
				dataRomanNumeralString.setError(eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES);
			}
			else
			{
				// need to woek this out
				dataRomanNumeralString.decimalValue -= decrementValue;
			}

			localInputData.counters[(int) indexOfRomanNumeral - 1] = COUNT_AFTER_SUBRTACT_VALUE;
		}
	}
	localInputData.indexLastValue = (int) indexOfRomanNumeral;
}
