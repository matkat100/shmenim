#pragma once
#include "Piece.h"
class Knight : public Piece
{
public:
	Knight(const std::string& color);
	std::string getColor() const override;
	std::string getType() const override;
};