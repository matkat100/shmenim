#pragma once
#include <iostream>

class Player
{
protected:
	std::string _color;
	static bool _myTurn;
public:
	Player(std::string color);
	std::string getColor() const;
	void switchTurn();
	bool isMyTurn() const;
};

