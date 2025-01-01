#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:
	Queen(const std::string& color);
	std::string getColor() const override;
	std::string getType() const override;
};