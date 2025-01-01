#pragma once
#include "Piece.h"
class King: public Piece
{
public:
	King(const std::string& color);
	std::string getColor() const override;
	std::string getType() const override;
};

