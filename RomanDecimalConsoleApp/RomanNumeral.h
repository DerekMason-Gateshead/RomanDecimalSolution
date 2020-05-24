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
// Base class for an individual roman numeral
class RomanNumeral
{
public:
	RomanNumeral();
	virtual ~RomanNumeral();

	// will store value of data 1,5,10, etc
	int value; 
	virtual void HandleInput() = 0;
	

};

