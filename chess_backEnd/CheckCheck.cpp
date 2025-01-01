#include "CheckCheck.h"

Piece* CheckCheck::checkPieceByJump(std::vector<Piece*> pieces, int destLocation, int jump) const
{
    destLocation -= jump;
    while (destLocation >= 0 && destLocation < 64)
    {
        if (pieces[destLocation] != nullptr) { return pieces[destLocation]; }
        destLocation -= jump;
    }
    return nullptr;
}

int CheckCheck::checkDiagonal(std::vector<Piece*> pieces, int destLocation, bool isWhiteKing) const
{
    Piece* upperLeft = checkPieceByJump(pieces, destLocation, -9);
    Piece* upperRight = checkPieceByJump(pieces, destLocation, -7);
    Piece* lowerLeft = checkPieceByJump(pieces, destLocation, 7);
    Piece* lowerRight = checkPieceByJump(pieces, destLocation, 9);
    return this->isDiagonalThreat(upperLeft, isWhiteKing) || this->isDiagonalThreat(upperRight, isWhiteKing) ||
        this->isDiagonalThreat(lowerLeft, isWhiteKing) || this->isDiagonalThreat(lowerRight, isWhiteKing);
}

bool CheckCheck::isDiagonalThreat(Piece* piece, bool isWhiteKing) const
{
    if (piece == nullptr) { return false; }
    std::string type = piece->getType();
    return (isWhiteKing ? (type == "b" || type == "q") : (type == "B" || type == "Q"));
}

int CheckCheck::checkVerticalHorizontal(std::vector<Piece*> pieces, int destLocation, bool isWhiteKing) const
{
    Piece* up = checkPieceByJump(pieces, destLocation, -8);
    Piece* down = checkPieceByJump(pieces, destLocation, 8);
    Piece* left = checkPieceByJump(pieces, destLocation, -1);
    Piece* right = checkPieceByJump(pieces, destLocation, 1);
    return this->isVerticalHorizontalThreat(up, isWhiteKing) || this->isVerticalHorizontalThreat(down, isWhiteKing) ||
        this->isVerticalHorizontalThreat(left, isWhiteKing) || this->isVerticalHorizontalThreat(right, isWhiteKing);
}

bool CheckCheck::isVerticalHorizontalThreat(Piece* piece, bool isWhiteKing) const
{
    if (piece == nullptr) { return false; }
    std::string type = piece->getType();
    return (isWhiteKing ? (type == "r" || type == "q") : (type == "R" || type == "Q"));
}

int CheckCheck::checkKnight(std::vector<Piece*> pieces, int destLocation, bool isWhiteKing) const
{
    int knightMoves[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };
    for (int move : knightMoves)
    {
        int targetLocation = destLocation + move;
        if (targetLocation >= 0 && targetLocation < 64) {
            Piece* piece = pieces[targetLocation];
            if (this->isKnightThreat(piece, isWhiteKing)) { return true; }
        }
    }
    return false;
}

bool CheckCheck::isKnightThreat(Piece* piece, bool isWhiteKing) const
{
    if (piece == nullptr) { return false; }
    std::string type = piece->getType();
    return (isWhiteKing ? (type == "n") : (type == "N"));
}

int CheckCheck::checkPawn(std::vector<Piece*> pieces, int destLocation, bool isWhiteKing) const
{
    int pawnAttacks[2] = { -9, -7 };
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
                ((isWhiteKing && piece->getType() == "p") || (!isWhiteKing && piece->getType() == "P"))) {
                return true;
            }
        }
    }
    return false;
}

int CheckCheck::Combinecheck(std::vector<Piece*> pieces, int kingLocation) const
{
    Piece* king = pieces[kingLocation];
    if (king == nullptr) {
        return false;
    }
    std::string kingType = king->getType();
    bool isWhiteKing = (kingType == "K");
    if (checkDiagonal(pieces, kingLocation, isWhiteKing) ||
        checkVerticalHorizontal(pieces, kingLocation, isWhiteKing) ||
        checkKnight(pieces, kingLocation, isWhiteKing) ||
        checkPawn(pieces, kingLocation, isWhiteKing))
    {
        return true;
    }
    return false;
}

bool CheckCheck::isCheckmate(std::vector<Piece*> pieces, int kingLocation) const
{
    if (!this->Combinecheck(pieces, kingLocation)) {
        return false;
    }

    int kingMoves[8] = { -9, -8, -7, -1, 1, 7, 8, 9 };
    for (int move : kingMoves)
    {
        int targetLocation = kingLocation + move;
        if (targetLocation >= 0 && targetLocation < 64) {
            Piece* targetPiece = pieces[targetLocation];
            if (targetPiece == nullptr || targetPiece->getColor() != pieces[kingLocation]->getColor()) {
                if (!Combinecheck(pieces, targetLocation)) {
                    return false;
                }
            }
        }
    }

    return true;
}

int CheckCheck::checkGameState(std::vector<Piece*> pieces, std::string currentPlayerColor) const
{
    bool isWhite = (currentPlayerColor == "White");
    bool isBlack = (currentPlayerColor == "Black");

    if (!isWhite && !isBlack) {
        return 5;  // Invalid color
    }

    int kingLocation = getKingLocation(pieces, currentPlayerColor);
    if (kingLocation == -1) {
        return 5;  // King not found (invalid)
    }

    bool isKingInCheck = Combinecheck(pieces, kingLocation);
    bool isKingInCheckmate = isCheckmate(pieces, kingLocation);

    if (isKingInCheckmate) {
        return 8;  // Checkmate
    }

    if (isKingInCheck) {
        return 1;  // Check
    }

    return 0;  // Normal move
}

int CheckCheck::getKingLocation(std::vector<Piece*> pieces, std::string currentPlayerColor) const
{
    for (int i = 0; i < 64; ++i) {
        Piece* piece = pieces[i];
        if (piece != nullptr && piece->getColor() == currentPlayerColor && (piece->getType() == "K" || piece->getType() == "k")) {
            return i;
        }
    }
    return -1;  // King not found
}
