#include "SimpleCheck.h"
#include <stdexcept>

using std::cout;

bool SimpleCheck::theSameSquare(std::string move) const {
    return move[0] == move[2] && move[1] == move[3];
}

bool SimpleCheck::currentSquareIsUnoccupiedByPlayer(std::string move, std::vector<Piece*> pieces, std::string currentPlayer) const {
    if (move.size() != 4 || pieces.size() < 64) return false;

    int current = (move[0] - 'a') + (8 * (7 - (move[1] - '1')));
    if (current < 0 || current >= 64 || pieces[current] == nullptr) return true;

    return pieces[current]->getColor() != currentPlayer;
}

bool SimpleCheck::NextSquareIsOccupiedByPlayer(std::string move, std::vector<Piece*> pieces, std::string currentPlayer) const {
    if (move.size() != 4 || pieces.size() < 64) return false;

    int dest = (move[2] - 'a') + (8 * (7 - (move[3] - '1')));
    if (dest < 0 || dest >= 64 || pieces[dest] == nullptr) return false;

    return pieces[dest]->getColor() == currentPlayer;
}

bool SimpleCheck::moveCheck(std::string move, std::vector<Piece*> pieces) const {
    if (move.size() != 4 || pieces.size() < 64) return false;

    int src = (move[0] - 'a') + (8 * (7 - (move[1] - '1')));  // Source index
    int dst = (move[2] - 'a') + (8 * (7 - (move[3] - '1')));  // Destination index

    if (src < 0 || src >= 64 || dst < 0 || dst >= 64 || pieces[src] == nullptr) return false;

    std::string currentPiece = pieces[src]->getType();

    // Handle King movement
    if (currentPiece == "K" || currentPiece == "k") {
        if (abs(move[2] - move[0]) > 1 || abs(move[3] - move[1]) > 1) return false;  // King moves 1 square in any direction
    }

    // Handle Bishop movement
    if (currentPiece == "B" || currentPiece == "b") {
        if (abs(move[2] - move[0]) != abs(move[3] - move[1])) return false;  // Bishop moves diagonally
        if (!isPathClear(move[0], move[1], move[2], move[3], pieces)) return false;  // Check if path is clear
    }

    // Handle Rook movement
    if (currentPiece == "R" || currentPiece == "r") {
        if (!(move[0] == move[2] || move[1] == move[3])) return false;  // Rook moves horizontally or vertically
        if (!isPathClear(move[0], move[1], move[2], move[3], pieces)) return false;  // Check if path is clear
    }

    // Handle Queen movement (combination of Bishop and Rook)
    if (currentPiece == "Q" || currentPiece == "q") {
        if (!(move[0] == move[2] || move[1] == move[3] || abs(move[2] - move[0]) == abs(move[3] - move[1]))) return false;
        if (!isPathClear(move[0], move[1], move[2], move[3], pieces)) return false;  // Check if path is clear
    }

    // Handle Knight movement
    if (currentPiece == "N" || currentPiece == "n") {
        int dx = abs(move[2] - move[0]);
        int dy = abs(move[3] - move[1]);
        if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) return false;  // Knight moves in "L" shape
    }


    // Handle Pawn movement
    if (currentPiece == "P" || currentPiece == "p") {
        int direction = (currentPiece == "P") ? -1 : 1;  // White pawns move up (-1), Black pawns move down (+1)
        int dx = move[2] - move[0];  // Horizontal difference
        int dy = move[3] - move[1];  // Vertical difference

        // Calculate srcIdx and dstIdx using your method
        int srcIdx = (move[0] - 'a') + (8 * (7 - (move[1] - '1')));  // Source index
        int dstIdx = (move[2] - 'a') + (8 * (7 - (move[3] - '1')));  // Destination index

        // Single forward move (Pawn moves one square forward)
        if (dx == 0 && dy == direction) {
            if (pieces[dstIdx] == nullptr) return false;  // Destination must be empty
        }
        // Double forward move (Only from initial rows: 1 for black, 6 for white)
        else if (dx == 0 && dy == 2 * direction) {
            int initialRow = (currentPiece == "P") ? 6 : 1;  // White starts at row 6, Black at row 1
            int srcRow = 8 - (move[1] - '1');  // Source row (0-indexed)
            int midIdx = srcIdx + (direction * 8);  // Middle square index
            if (srcRow != initialRow || pieces[midIdx] != nullptr || pieces[dstIdx] != nullptr) return false;  // Path must be clear
        }
        // Diagonal capture (Pawn moves diagonally to capture)
        else if (abs(dx) == 1 && dy == direction) {
            if (pieces[dstIdx] == nullptr || pieces[dstIdx]->getColor() == pieces[srcIdx]->getColor()) return false;  // Must capture opponent
        }
    }
    return true;
}


bool SimpleCheck::isPathClear(char startX, char startY, char endX, char endY, std::vector<Piece*> pieces) const {
    int dx = (endX > startX) ? 1 : (endX < startX) ? -1 : 0;
    int dy = (endY > startY) ? 1 : (endY < startY) ? -1 : 0;

    char x = startX + dx;
    char y = startY + dy;

    while (x != endX || y != endY) {
        if (x < 'a' || x > 'h' || y < '1' || y > '8') return false;
        int idx = (x - 'a') + (8 * (7 - (y - '1')));
        if (pieces[idx] != nullptr) return false;

        x += dx;
        y += dy;
    }

    return true;
}

int SimpleCheck::combineCheck(std::string move, std::vector<Piece*> pieces, std::string currentPlayer) const {
    if (this->theSameSquare(move)) return 7;
    if (this->currentSquareIsUnoccupiedByPlayer(move, pieces, currentPlayer)) return 2;
    if (this->NextSquareIsOccupiedByPlayer(move, pieces, currentPlayer)) return 3;
    if (!this->moveCheck(move, pieces)) return 6;
    return 0;
}
