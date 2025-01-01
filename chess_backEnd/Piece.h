#pragma once
#include <iostream>
class Piece
{
public:
    virtual std::string getColor() const = 0;
    virtual std::string getType() const = 0;
protected:
    std::string _color;
    std::string _type;
};