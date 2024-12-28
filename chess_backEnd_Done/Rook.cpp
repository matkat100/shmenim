#include "Rook.h"

std::string Rook::getType()
{
	if (this->_color == "White") { return "R"; }
	return "r";
}