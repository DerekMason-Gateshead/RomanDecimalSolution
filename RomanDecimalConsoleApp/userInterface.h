#pragma once
#include <iostream>
class userInterface
{

public:
	void run();
	void InitialMenu();
	void InputRomanMenu();

private:
	enum class MenuState
	{
		Init,
		InputRoman
	};

	bool runMenu = true;
	MenuState m_eMenuState = MenuState::Init;
};

