#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include "Piece.h"
class SimpleCheck
{
public:
	bool legalSquare(std::string move);
	bool theSameSquare(std::string move);
	bool currentSquareIsUnoccupiedByPlayer(std::string move, std::vector<Piece*> pieces, std::string currentPlayer);
	bool NextSquareIsOccupiedByPlayer(std::string move, std::vector<Piece*> pieces, std::string currentPlayer);
	int combineCheck(std::string move, std::vector<Piece*> pieces, std::string currentPlayer);
	bool moveCheck(std::string move, std::vector<Piece*> pieces);
};

