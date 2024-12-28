#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include "Piece.h"

class CheckCheck
{
public:
    static int _checkWhite, _checkBlack;
    Piece* checkPieceByJump(const std::vector<Piece*>& pieces, int destLocation, int jump) const;
    int checkDiagonal(const std::vector<Piece*>& pieces, int destLocation, bool isWhiteKing) const;
    int checkVerticalHorizontal(const std::vector<Piece*>& pieces, int destLocation, bool isWhiteKing) const;
    int checkKnight(const std::vector<Piece*>& pieces, int destLocation, bool isWhiteKing) const;
    int checkPawn(const std::vector<Piece*>& pieces, int destLocation, bool isWhiteKing) const;
    bool Combinecheck(const std::vector<Piece*>& pieces, const std::string& kingLocation) const;
    bool isDiagonalThreat(Piece* piece, bool isWhiteKing) const;
    bool isKnightThreat(Piece* piece, bool isWhiteKing) const;
    bool isVerticalHorizontalThreat(Piece* piece, bool isWhiteKing) const;
};