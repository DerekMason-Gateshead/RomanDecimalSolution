#include "userInterface.h"
#include <string>
using namespace std;
#include <conio.h>
#include "RomanNumeralData.h"




void userInterface::run()
{

	while (runMenu)
	{
		switch (m_eMenuState)
		{
		case MenuState::Init:
			InitialMenu();
			break;
		case MenuState::InputRoman:
			InputRomanMenu();
			break;
		case MenuState::InputDecimal:
			InputDecimalData();
			break;
		default:
			break;
		}

	}

}

void userInterface::InitialMenu()
{
	std::cout << "1: Input Roman Data (to convert to decimal)\n"
			  << "2: Input Decimal Data (to conver to roman numeral)\n"
			  << "Q - Quit" << endl;

	char c = _getch();
	
	switch (c)
	{
	case '1':
		m_eMenuState = MenuState::InputRoman;
		break;
	case '2':
		m_eMenuState = MenuState::InputDecimal;
		break;
	case 'q':
	case 'Q':
		runMenu = false;
		break;
	default:
		std::cout << "\n\n1: Invalid Input\n\n";
		
		break;
	}
	

}

void userInterface::InputRomanMenu()
{
	std::cout << "Input Roman Numeral (^V for 5000) and (^X for 10000) : ";
	std::string input;
	int nValue;
	getline(cin, input);

	RomanNumeralData romanData;

	romanData.setRomanNumeralData(input);
	
	if (romanData.IsDataValid())
	{
		nValue = romanData.romanDecimalValue();
		std::cout << "\nDecimal Value : " <<  nValue << "\n\n";
	} 
	else
	{
		std::cout << "\nInvalid Data \n\n";

	}

	m_eMenuState = MenuState::Init;
}

void userInterface::InputDecimalData()
{
	std::cout << "Input Decimal Value : ";
	std::string input;
	std::string output;
	int nValue;
	getline(cin, input);

	RomanNumeralData romanData;

	bool passed = romanData.getRomanNumeral(input, output);

	

	if (passed)
	{
		for (int i = 0; i < output.length(); i++)
		{
			if (output[i] == '^')
			{
				std::cout << "\nNote ^V (roman 5000) ^X (roman 10000) : " << "\n";

				break;
			}
		}
		std::cout << "\nRoman Numeral : " << output.c_str() << "\n\n";

		
	}
	else
	{
		std::cout << "\nInvalid Data \n\n";

	}

	m_eMenuState = MenuState::Init;
}
