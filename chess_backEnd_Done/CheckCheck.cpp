#include "CheckCheck.h"

Piece* CheckCheck::checkPieceByJump(const std::vector<Piece*>& pieces, int destLocation, int jump) const
{
    destLocation -= jump;
    while (destLocation >= 0 && destLocation < 64)
    {
        if (pieces[destLocation] != nullptr) { return pieces[destLocation]; }
        destLocation -= jump;
    }
    return nullptr;
}

int CheckCheck::checkDiagonal(const std::vector<Piece*>& pieces, int destLocation, bool isWhiteKing) const
{
    Piece* upperLeft = checkPieceByJump(pieces, destLocation, -9);
    Piece* upperRight = checkPieceByJump(pieces, destLocation, -7);
    Piece* lowerLeft = checkPieceByJump(pieces, destLocation, 7);
    Piece* lowerRight = checkPieceByJump(pieces, destLocation, 9);

    return isDiagonalThreat(upperLeft, isWhiteKing) || isDiagonalThreat(upperRight, isWhiteKing) ||
        isDiagonalThreat(lowerLeft, isWhiteKing) || isDiagonalThreat(lowerRight, isWhiteKing);
}

bool CheckCheck::isDiagonalThreat(Piece* piece, bool isWhiteKing) const
{
    if (piece == nullptr) { return false; }
    std::string type = piece->getType();
    return isWhiteKing ? (type == "b" || type == "q") : (type == "B" || type == "Q");
}

int CheckCheck::checkVerticalHorizontal(const std::vector<Piece*>& pieces, int destLocation, bool isWhiteKing) const
{
    Piece* up = checkPieceByJump(pieces, destLocation, -8);
    Piece* down = checkPieceByJump(pieces, destLocation, 8);
    Piece* left = checkPieceByJump(pieces, destLocation, -1);
    Piece* right = checkPieceByJump(pieces, destLocation, 1);

    return isVerticalHorizontalThreat(up, isWhiteKing) || isVerticalHorizontalThreat(down, isWhiteKing) ||
        isVerticalHorizontalThreat(left, isWhiteKing) || isVerticalHorizontalThreat(right, isWhiteKing);
}

bool CheckCheck::isVerticalHorizontalThreat(Piece* piece, bool isWhiteKing) const
{
    if (piece == nullptr) { return false; }
    std::string type = piece->getType();
    return isWhiteKing ? (type == "r" || type == "q") : (type == "R" || type == "Q");
}

int CheckCheck::checkKnight(const std::vector<Piece*>& pieces, int destLocation, bool isWhiteKing) const
{
    int knightMoves[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };
    for (int move : knightMoves)
    {
        int targetLocation = destLocation + move;
        if (targetLocation >= 0 && targetLocation < 64)
        {
            Piece* piece = pieces[targetLocation];
            if (isKnightThreat(piece, isWhiteKing)) { return true; }
        }
    }
    return false;
}

bool CheckCheck::isKnightThreat(Piece* piece, bool isWhiteKing) const
{
    if (piece == nullptr) { return false; }
    std::string type = piece->getType();
    return isWhiteKing ? (type == "n") : (type == "N");
}

int CheckCheck::checkPawn(const std::vector<Piece*>& pieces, int destLocation, bool isWhiteKing) const
{
    int pawnAttacks[2] = { -9, -7 };  // Default for white pawns
    if (!isWhiteKing) {
        pawnAttacks[0] = 7;
        pawnAttacks[1] = 9;
    }
    for (int attack : pawnAttacks)
    {
        int targetLocation = destLocation + attack;
        if (targetLocation >= 0 && targetLocation < 64)
        {
            Piece* piece = pieces[targetLocation];
            if (piece != nullptr &&
                ((isWhiteKing && piece->getType() == "p") || (!isWhiteKing && piece->getType() == "P")))
            {
                return true;
            }
        }
    }
    return false;
}

bool CheckCheck::Combinecheck(const std::vector<Piece*>& pieces, const std::string& kingLocation) const
{
    std::string currentLocation = kingLocation.substr(0, 2);
    std::string nextLocation = (kingLocation.size() > 2) ? kingLocation.substr(2) : "";
    int destLocation = 0;

    if (nextLocation.empty())
    {
        destLocation = (currentLocation[0] - 'a') + (8 - (currentLocation[1] - '0')) * 8;
    }
    else
    {
        destLocation = (nextLocation[0] - 'a') + (8 - (nextLocation[1] - '0')) * 8;
    }

    Piece* king = pieces[destLocation];
    if (king == nullptr)
    {
        return false; // No king at this location
    }

    std::string kingType = king->getType();
    bool isWhiteKing = (kingType == "K");

    return checkDiagonal(pieces, destLocation, isWhiteKing) ||
        checkVerticalHorizontal(pieces, destLocation, isWhiteKing) ||
        checkKnight(pieces, destLocation, isWhiteKing) ||
        checkPawn(pieces, destLocation, isWhiteKing);
}
