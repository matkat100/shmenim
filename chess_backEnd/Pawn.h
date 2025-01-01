#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	Pawn(const std::string& color);
	std::string getColor() const override;
	std::string getType() const override;
};

