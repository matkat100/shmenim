#include "Rook.h"

Rook::Rook(const std::string& color)
{
    _color = color;
    _type = (color == "White") ? "R" : "r";
}

std::string Rook::getColor() const { return _color; }

std::string Rook::getType() const { return _type; }