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
		default:
			break;
		}

	}

}

void userInterface::InitialMenu()
{
	std::cout << "1: Input Roman Data\n"
			  << "Q - Quit" << endl;

	char c = _getch();
	
	switch (c)
	{
	case '1':
		m_eMenuState = MenuState::InputRoman;
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
	std::cout << "Input Roman Numeral : ";
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
