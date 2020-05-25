#include "FullRomanNumeral.h"

// this handles all unit and 10 x unit data
// this effects data in dataRomanNumeralString and localInputData
// dataRomanNumeralString has it decimal value updates and if an error the status info
// localInputData - the counter for this index and the last index are updated, other counter 
//  info is used for error checking, lastIndex is used to check for pre roman numerals
void FullRomanNumeral::HandleInput(dataForRomanNumeralInput& dataRomanNumeralString, localDataForRomanNumeralInput& localInputData)
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

	dataRomanNumeralString.decimalValue += incrementValue;

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

	localInputData.indexLastValue = index;
}
