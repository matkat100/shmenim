#include "Queen.h"

Queen::Queen(const std::string& color)
{
    _color = color;
    _type = (color == "White") ? "Q" : "q";
}

std::string Queen::getColor() const { return _color; }

std::string Queen::getType() const { return _type; }