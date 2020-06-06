#include "RomanNumeralValue.h"
#include "FullRomanNumeral.h"
RomanNumeralValue::RomanNumeralValue()
{
	indexLastNumeral = -1;
	for (int i = 0; i < (int)RomanIndex::FINAL_INDEX; i++)
	{
		counters[i] = 0;
	}

	valid = true;
	statusCode = eStatusCode::eSUCCESS;
}

void RomanNumeralValue::AddValue(RomanNumeral& numeral)
{
	if (dynamic_cast<FullRomanNumeral*>(&numeral) == nullptr)
	{
		AddFiveBaseValue(numeral);
	}
	else
	{
		AddTenBaseValue(numeral);
	}
}

void RomanNumeralValue::AddFiveBaseValue(RomanNumeral& numeral)
{
	#define OFFSET_FOR_INDEX_CHECK_COMPLETE 2
	// we need to check that invalid counters have not been called
	if ((int) numeral.getIndex() > (int)RomanIndex::INDEX_V)
	{
		// check from 0 to two indexes below current value
		for (int i = 0; i <= ((int) numeral.getIndex() - OFFSET_FOR_INDEX_CHECK_COMPLETE); i++)
		{
			if (counters[i] > 0)
			{
				setError(eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER);
				return;
			}
		}
	}

	counters[(int) numeral.getIndex()]++;
	decimalValue += numeral.getIncrementValue();

	// we should never have more than one instance of a half value
	if (counters[(int) numeral.getIndex()] > MAX_HALF_ROMAN_NUMERALS)
	{
		setError(eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES);
		return;
	}

	// this stuff is rependent on last value do if last value is index -1 
	if (((int) numeral.getIndex() > 0) && (indexLastNumeral >= 0))
	{
	if (((int) numeral.getIndex() > 0) && (indexLastNumeral >= 0))
		if (((int) numeral.getIndex() - 1) == indexLastNumeral)
		{
			if (counters[(int) numeral.getIndex() - 1] > MAX_PRE_BASE_TEN)
			{
				setError(eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES);
			}
			else
			{
				// need to woek this out
				decimalValue -= numeral.getDecrementValue();
			}

			counters[(int) numeral.getIndex() - 1] = COUNT_AFTER_SUBRTACT_VALUE;
		}
	}

	indexLastNumeral = (int)numeral.getIndex();
}

#define OFFSET_FOR_FULL_INDEX_CHECK_COMPLETE 3

void RomanNumeralValue::AddTenBaseValue(RomanNumeral& numeral)
{
	// we need to check that invalid counters have not been called
	if (doesInvalidRomanNumeralPreceedThisNumeral((int)numeral.getIndex(), OFFSET_FOR_FULL_INDEX_CHECK_COMPLETE))
	{
		setError(eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER);
		return;
	}

	counters[(int)numeral.getIndex()]++;


	decimalValue += numeral.getIncrementValue();

	// this stuff is rependent on last value do if last value is index -1 
	if (((int)numeral.getIndex() > 1) && (indexLastNumeral >= 0))
	{
		if (((int)numeral.getIndex() - 2) == indexLastNumeral)
		{
			if (counters[indexLastNumeral] > MAX_PRE_BASE_TEN)
			{
				setError(eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES);
				return;
			}
			else
			{
				// need to woek this out
				decimalValue -= numeral.getDecrementValue();
			}

			counters[indexLastNumeral] = COUNT_AFTER_SUBRTACT_VALUE;

			counters[(int)numeral.getIndex()] = MAX_BASE10_VALUES;

		}
	}

	if (counters[(int)numeral.getIndex()] > MAX_BASE10_VALUES)
	{
		setError(eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES);
	}

	indexLastNumeral = (int) numeral.getIndex();
}

void RomanNumeralValue::setError(eStatusCode Code)
{
	valid = false;
	statusCode = Code;
}

const bool RomanNumeralValue::doesInvalidRomanNumeralPreceedThisNumeral(int indexOfRomanNumeral, int offset)
{

	if ((int)indexOfRomanNumeral > (int)RomanIndex::INDEX_V)
	{
		// check from 0 to indexes below current value
		for (int i = 0; i <= ((int)indexOfRomanNumeral - offset); i++)
		{
			if (counters[i] > 0)
			{
				return true;
			}
		}
	}

	if ((int)indexOfRomanNumeral > 0)
	{
		// one index less must be a half value which cannot be pre this
		if (counters[(int)indexOfRomanNumeral - 1] > 0)
		{
			return true;
		}
	}

	return false;
}