#pragma once
#include "Piece.h"
class King : protected Piece
{
public:
	std::string getType() override;
};

