#include "SimpleCheck.h"

bool SimpleCheck::legalSquare(std::string move)
{
	int current = (move[0] - (char)96) * (move[1] - '0');
	int dest = (move[2] - 'a') * (move[3] - '0');
	return current <= 64 && current > 0 && dest <= 64 && dest > 0;
}

bool SimpleCheck::theSameSquare(std::string move)
{
	if (move[0] == move[2] && move[1] == move[3])
	{
		return true;
	}
	return false;
}

bool SimpleCheck::currentSquareIsUnoccupiedByPlayer(std::string move, std::vector<Piece*> pieces, std::string currentPlayer)
{
	int square = 0;
	square += (move[0] - 'a') * 10;
	square += move[1] - '0';
	if (pieces[square] == NULL) { return true; }
	if (pieces[square]->getType() >= "a" && pieces[square]->getType() <= "z")
	{
		return currentPlayer != "Black";
	}
	return currentPlayer != "White";
}

bool SimpleCheck::NextSquareIsOccupiedByPlayer(std::string move, std::vector<Piece*> pieces, std::string currentPlayer)
{
	int square = 0;
	square += (move[2] - 'a') * 10;
	square += move[3] - '0';
	if (pieces[square] == NULL) { return true; }
	if (pieces[square]->getType() >= "a" && pieces[square]->getType() <= "z")
	{
		return currentPlayer == "Black";
	}
	return currentPlayer == "White";
}

int SimpleCheck::combineCheck(std::string move, std::vector<Piece*> pieces, std::string currentPlayer)
{
	if (this->theSameSquare(move)) { return 7; }
	if (this->currentSquareIsUnoccupiedByPlayer(move, pieces, currentPlayer)) { return 2; }
	if (this->NextSquareIsOccupiedByPlayer(move, pieces, currentPlayer)) { return 3; }
	if (this->moveCheck(move, pieces)) { return 5; }
	return 0;
}

bool SimpleCheck::moveCheck(std::string move, std::vector<Piece*> pieces)
{
	int current = (move[0] - (char)96) * (move[1] - '0');
	std::string currentPiece = pieces[current]->getType();
	if (currentPiece == "K" || currentPiece == "k")
	{
		if ((move[2] - move[0] > 1 || move[2] - move[0] < -1)
			|| (move[3] - move[1] > 1 || move[3] - move[1] < -1))
		{
			return false;
		}
	}
	if (currentPiece == "B" || currentPiece == "b")
	{
		if (move[2] - move[0] != move[3] - move[1])
		{
			return false;
		}
	}
	if (currentPiece == "R" || currentPiece == "r")
	{
		if (!((move[0] == move[2] && move[1] != move[3]) ||
			(move[0] != move[2] && move[1] == move[3])))
		{
			return false;
		}

		return true;
	}
	return NULL;
}
