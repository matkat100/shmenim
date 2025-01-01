#include "King.h"

King::King(const std::string& color)
{
    _color = color;
    _type = (color == "White") ? "K" : "k";
}

std::string King::getColor() const { return _color; }

std::string King::getType() const { return _type; }