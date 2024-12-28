#pragma once
#include <vector>
#include <string>
#include "Piece.h"
#include "Player.h"

class Protocol
{
private:
    static std::vector<Piece*> _Pieces; 

public:
    static int returnProtocolNum(const std::string& move, Player& currentPlayer);
};