#pragma once
#include <iostream>
#include <vector>
#include "Piece.h"

class CheckCheck
{
public:
    Piece* checkPieceByJump(std::vector<Piece*> pieces, int destLocation, int jump) const;
    int checkDiagonal(std::vector<Piece*> pieces, int destLocation, bool isWhiteKing) const;
    bool isDiagonalThreat(Piece* piece, bool isWhiteKing) const;
    int checkVerticalHorizontal(std::vector<Piece*> pieces, int destLocation, bool isWhiteKing) const;
    bool isVerticalHorizontalThreat(Piece* piece, bool isWhiteKing) const;
    int checkKnight(std::vector<Piece*> pieces, int destLocation, bool isWhiteKing) const;
    bool isKnightThreat(Piece* piece, bool isWhiteKing) const;
    int checkPawn(std::vector<Piece*> pieces, int destLocation, bool isWhiteKing) const;
    int Combinecheck(std::vector<Piece*> pieces, int kingLocation) const;
    int checkGameState(std::vector<Piece*> pieces, std::string currentPlayerColor) const;
    int getKingLocation(std::vector<Piece*> pieces, std::string currentPlayerColor) const;
    bool isCheckmate(std::vector<Piece*> pieces, int kingLocation) const;
};