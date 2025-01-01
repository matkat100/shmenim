#pragma once
#include <iostream>
#include <vector>
#include "Piece.h"
class SimpleCheck
{
public:
	bool legalSquare(std::string move) const;
	bool theSameSquare(std::string move) const;
	bool currentSquareIsUnoccupiedByPlayer(std::string move, std::vector<Piece*> pieces, std::string currentPlayer) const;
	bool NextSquareIsOccupiedByPlayer(std::string move, std::vector<Piece*> pieces, std::string currentPlayer) const;
	bool moveCheck(std::string move, std::vector<Piece*> pieces) const;
	bool isPathClear(char startX, char startY, char endX, char endY, std::vector<Piece*> pieces) const;
	int combineCheck(std::string move, std::vector<Piece*> pieces, std::string currentPlayer) const;
};