#include "Knight.h"

Knight::Knight(const std::string& color)
{
    _color = color;
    _type = (color == "White") ? "N" : "n";
}

std::string Knight::getColor() const { return _color; }

std::string Knight::getType() const { return _type; }