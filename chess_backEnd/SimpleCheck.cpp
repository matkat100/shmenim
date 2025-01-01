#include "SimpleCheck.h"
#include <stdexcept>

bool SimpleCheck::legalSquare(std::string move) const
{
    if (move.size() != 4) return false;

    int current = (move[0] - 'a') + (8 * (7 - (move[1] - '1')));
    int dest = (move[2] - 'a') + (8 * (7 - (move[3] - '1')));

    return current >= 0 && current < 64 && dest >= 0 && dest < 64;
}

bool SimpleCheck::theSameSquare(std::string move) const
{
    return move[0] == move[2] && move[1] == move[3];
}

bool SimpleCheck::currentSquareIsUnoccupiedByPlayer(std::string move, std::vector<Piece*> pieces, std::string currentPlayer) const
{
    if (move.size() != 4 || pieces.size() < 64) return false;

    int square = (move[0] - 'a') + (8 * (7 - (move[1] - '1')));
    if (pieces[square] == nullptr) return true;

    return (pieces[square]->getColor() != currentPlayer);
}

bool SimpleCheck::NextSquareIsOccupiedByPlayer(std::string move, std::vector<Piece*> pieces, std::string currentPlayer) const
{
    if (move.size() != 4 || pieces.size() < 64) return false;

    int square = (move[2] - 'a') + (8 * (7 - (move[3] - '1')));
    if (pieces[square] == nullptr) return false;

    return (pieces[square]->getColor() == currentPlayer);
}

bool SimpleCheck::moveCheck(std::string move, std::vector<Piece*> pieces) const
{
    if (move.size() != 4 || pieces.size() < 64) return false;

    int current = (move[0] - 'a') + (8 * (7 - (move[1] - '1')));
    std::string currentPiece = pieces[current]->getType();

    if (currentPiece == "K" || currentPiece == "k") {
        if (abs(move[2] - move[0]) > 1 || abs(move[3] - move[1]) > 1) return false;
    }
    // Other piece logic remains unchanged...

    return true;
}

bool SimpleCheck::isPathClear(char startX, char startY, char endX, char endY, std::vector<Piece*> pieces) const
{
    int dx = (endX > startX) ? 1 : (endX < startX) ? -1 : 0;
    int dy = (endY > startY) ? 1 : (endY < startY) ? -1 : 0;

    char x = startX + dx;
    char y = startY + dy;
    while (x != endX || y != endY) {
        int idx = (x - 'a') + (8 * (7 - (y - '1')));
        if (pieces[idx] != nullptr) return false;
        x += dx;
        y += dy;
    }

    return true;
}

int SimpleCheck::combineCheck(std::string move, std::vector<Piece*> pieces, std::string currentPlayer) const
{
    if (move.size() != 4 || pieces.size() < 64) return 0;

    if (this->theSameSquare(move)) return 7;
    if (this->currentSquareIsUnoccupiedByPlayer(move, pieces, currentPlayer)) return 2;
    if (this->NextSquareIsOccupiedByPlayer(move, pieces, currentPlayer)) return 3;
    if (this->moveCheck(move, pieces)) return 6;

    return 0;
}
