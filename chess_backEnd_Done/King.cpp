#include "King.h"

std::string King::getType()
{
	if (this->_color == "White") { return "K"; }
	return "k";
}