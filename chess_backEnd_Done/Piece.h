#pragma once
#include "Player.h"

class Piece : public Player
{
public:
	virtual std::string getType() = 0;
protected:
	std::string _type;
};