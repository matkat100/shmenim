#pragma once
#include "Piece.h"
#include <string>
class Pawn : protected Piece
{
public:
	std::string getType() override;
};