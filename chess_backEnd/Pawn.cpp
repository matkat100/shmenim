#include "Pawn.h"

Pawn::Pawn(const std::string& color)
{
    _color = color;
    _type = (color == "White") ? "P" : "p";
}

std::string Pawn::getColor() const { return _color; }

std::string Pawn::getType() const { return _type; }