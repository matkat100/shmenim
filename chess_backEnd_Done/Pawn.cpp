#include "Pawn.h"

std::string Pawn::getType()
{
	if (this->_color == "White") { return "R"; }
	return "r";
}