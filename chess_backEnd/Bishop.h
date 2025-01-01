#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop(const std::string & color);
	std::string getColor() const override;
	std::string getType() const override;
};