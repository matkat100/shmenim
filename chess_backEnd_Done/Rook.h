#pragma once
#include "Piece.h"
#include <string>
class Rook : protected Piece
{
public:
	std::string getType() override;
};