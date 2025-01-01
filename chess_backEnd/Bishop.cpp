#include "Bishop.h"

Bishop::Bishop(const std::string& color)
{
    _color = color;
    _type = (color == "White") ? "B" : "b";
}

std::string Bishop::getColor() const { return _color; }

std::string Bishop::getType() const { return _type; }