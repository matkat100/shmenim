#include "Player.h"

bool Player::_myTurn = true;
Player::Player(std::string color) : _color(color)
{
    if (color == "White")
    {
        Player::_myTurn = true;
    }
    else
    {
        Player::_myTurn = false;
    }
}

std::string Player::getColor() const
{
    return this->_color;
}


void Player::switchTurn()
{
    _myTurn = !_myTurn;
}

bool Player::isMyTurn() const
{
    return _myTurn;
}
