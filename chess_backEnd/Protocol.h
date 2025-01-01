#pragma once
#include "Piece.h"
#include "SimpleCheck.h"
#include "CheckCheck.h"

class Protocol
{
private:
    std::vector<Piece*> _pieces;
public:
    static bool isWhiteTurn;
    Protocol();
    ~Protocol();
    int returnProtocolNum(const std::string& move);
    void swapSquares(const std::string& move);
};

