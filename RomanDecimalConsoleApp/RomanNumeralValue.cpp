#include "RomanNumeralValue.h"

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
	if (numeral.IsHalfValue())
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
	int offsetForPreeceder = 1;
	// we need to check that invalid counters have not been called
	if (doesInvalidRomanNumeralPreceedThisNumeral((int)numeral.getIndex(), offsetForPreeceder))
	{
		setError(eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER);
		return;
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
	if (((int)numeral.getIndex() >= offsetForPreeceder) && (indexLastNumeral >= 0))
	{
		checkIfPrecedeededByDecrementer(numeral, offsetForPreeceder);		
	}
	indexLastNumeral = (int)numeral.getIndex();
}


void RomanNumeralValue::AddTenBaseValue(RomanNumeral& numeral)
{
	int offsetForPreeceder = 2;

	// we need to check that invalid counters have not been called
	if (doesInvalidRomanNumeralPreceedThisNumeral((int)numeral.getIndex(), offsetForPreeceder))
	{
		setError(eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER);
		return;
	}

	if (isTenBaseValueProceededByHalfValue((int)numeral.getIndex()))
	{
		setError(eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER);
		return;
	}
	counters[(int)numeral.getIndex()]++;


	decimalValue += numeral.getIncrementValue();

	// this stuff is rependent on last value do if last value is index -1 
	if (((int)numeral.getIndex() >= offsetForPreeceder) && (indexLastNumeral >= 0))
	{
		checkIfPrecedeededByDecrementer(numeral,offsetForPreeceder);
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
		for (int i = 0; i < ((int)indexOfRomanNumeral - offset); i++)
		{
			if (counters[i] > 0)
			{
				return true;
			}
		}
	}


	return false;
}

const bool RomanNumeralValue::isTenBaseValueProceededByHalfValue(int indexOfRomanNumeral)
{

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

void RomanNumeralValue::checkIfPrecedeededByDecrementer(RomanNumeral &numeral, int preceederOffset)
{
	if (((int)numeral.getIndex() - preceederOffset) == indexLastNumeral)
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

		if (!numeral.IsHalfValue())
		{
			counters[(int)numeral.getIndex()] = MAX_BASE10_VALUES;
		}
	}

}

