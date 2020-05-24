#pragma once
#include <iostream>
class userInterface
{

public:
	void run();
	void InitialMenu();
	void InputRomanMenu();
	void InputDecimalData();

private:
	enum class MenuState
	{
		Init,
		InputRoman,
		InputDecimal
	};

	bool runMenu = true;
	MenuState m_eMenuState = MenuState::Init;
};

