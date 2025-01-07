#include "CheckCheck.h"
#include <iostream>

using std::cout;

Piece* CheckCheck::checkPieceByJump(std::vector<Piece*> pieces, int destLocation, int jump) const
{
    destLocation -= jump;
    while (destLocation >= 0 && destLocation < 64)
    {
        // Ensure the piece does not wrap around rows.
        if (jump == -1 && destLocation % 8 == 7) break; // Moving left wraps to the previous row.
        if (jump == 1 && destLocation % 8 == 0) break;  // Moving right wraps to the next row.

        // Stop if the destination is out of valid chessboard rows.
        if (destLocation < 0 || destLocation >= 64) break;

        // Check if a piece is found.
        if (pieces[destLocation] != nullptr) return pieces[destLocation];

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
    if (piece == nullptr) return false;
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
    if (piece == nullptr) return false;
    std::string type = piece->getType();
    return (isWhiteKing ? (type == "r" || type == "q") : (type == "R" || type == "Q"));
}

int CheckCheck::checkKnight(std::vector<Piece*> pieces, int destLocation, bool isWhiteKing) const
{
    int knightMoves[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };
    for (int move : knightMoves)
    {
        int targetLocation = destLocation + move;
        if (targetLocation >= 0 && targetLocation < 64)
        {
            // Ensure knight doesn't jump across rows incorrectly.
            if (abs((destLocation % 8) - (targetLocation % 8)) > 2) continue;

            Piece* piece = pieces[targetLocation];
            if (this->isKnightThreat(piece, isWhiteKing)) return true;
        }
    }
    return false;
}

bool CheckCheck::isKnightThreat(Piece* piece, bool isWhiteKing) const
{
    if (piece == nullptr) return false;
    std::string type = piece->getType();
    return (isWhiteKing ? (type == "n") : (type == "N"));
}

int CheckCheck::checkPawn(std::vector<Piece*> pieces, int destLocation, bool isWhiteKing) const
{
    // Define pawn attack offsets.
    int pawnAttacks[2] = { -9, -7 }; // White pawns attack diagonally up.
    if (!isWhiteKing)
    {
        pawnAttacks[0] = 7;  // Black pawns attack diagonally down.
        pawnAttacks[1] = 9;
    }

    for (int attack : pawnAttacks)
    {
        int targetLocation = destLocation + attack;
        if (targetLocation >= 0 && targetLocation < 64)
        {
            // Ensure the attack doesn't wrap around rows.
            if (abs((destLocation % 8) - (targetLocation % 8)) != 1)
                continue;

            Piece* piece = pieces[targetLocation];
            if (piece != nullptr &&
                ((isWhiteKing && piece->getType() == "p") || (!isWhiteKing && piece->getType() == "P")))
            {
                return true; // Threat found.
            }
        }
    }

    return false; // No pawn threat.
}

int CheckCheck::Combinecheck(std::vector<Piece*> pieces, int kingLocation) const
{
    Piece* king = pieces[kingLocation];
    if (king == nullptr)
    {
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
    if (!this->Combinecheck(pieces, kingLocation))
    {
        return false;
    }

    int kingMoves[8] = { -9, -8, -7, -1, 1, 7, 8, 9 };
    for (int move : kingMoves)
    {
        int targetLocation = kingLocation + move;
        if (targetLocation >= 0 && targetLocation < 64)
        {
            // Ensure the king's move doesn't wrap rows.
            if (abs((kingLocation % 8) - (targetLocation % 8)) > 1) continue;

            Piece* targetPiece = pieces[targetLocation];
            if (targetPiece == nullptr || targetPiece->getColor() != pieces[kingLocation]->getColor())
            {
                if (!Combinecheck(pieces, targetLocation))
                {
                    return false;
                }
            }
        }
    }

    return true;
}

int CheckCheck::checkGameState(std::vector<Piece*> pieces, std::string currentPlayerColor) const
{
    int kingLocation = getKingLocation(pieces, currentPlayerColor);
    bool isKingInCheck = Combinecheck(pieces, kingLocation);
    bool isKingInCheckmate = isCheckmate(pieces, kingLocation);

    if (isKingInCheckmate)
    {
        return 8;  // Checkmate
    }

    if (isKingInCheck)
    {
        return 1;  // Check
    }

    return 0;  // Normal move
}

int CheckCheck::getKingLocation(std::vector<Piece*> pieces, std::string currentPlayerColor) const
{
    for (int i = 0; i < 64; i++)
    {
        Piece* piece = pieces[i];
        if (piece != nullptr && piece->getColor() == currentPlayerColor && (piece->getType() == "K" || piece->getType() == "k"))
        {
            return i;
        }
    }
    return -1; // Invalid index, king not found
}
