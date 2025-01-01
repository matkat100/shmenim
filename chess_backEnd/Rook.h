#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	Rook(const std::string& color);
	std::string getColor() const override;
	std::string getType() const override;
};