#include "Protocol.h"
#include <iostream>
#include <string>
#include "Piece.h"

std::vector<Piece*> Protocol::_Pieces(64, nullptr);

int Protocol::returnProtocolNum(const std::string& move, Player& currentPlayer)
{
    if (move.length() != 4)
    {
        return 5;
    }

    std::string source = move.substr(0, 2);
    std::string destination = move.substr(2, 2);

    int srcIndex = (source[0] - 'a') + (8 - (source[1] - '0')) * 8;
    int destIndex = (destination[0] - 'a') + (8 - (destination[1] - '0')) * 8;

    if (srcIndex < 0 || srcIndex >= 64 || destIndex < 0 || destIndex >= 64)
    {
        return 5; 
    }

    Piece* movingPiece = _Pieces[srcIndex];
    if (!movingPiece)
    {
        return 3; 
    }

    if (!currentPlayer.isMyTurn())
    {
        return 2;
    }

    if (movingPiece->getType() != currentPlayer.getColor())
    {
        return 2; 
    }

    if (source == destination)
    {
        return 7;
    }

    Piece* destinationPiece = _Pieces[destIndex];
    if (destinationPiece != nullptr && destinationPiece->getType() == movingPiece->getType())
    {
        return 3; 
    }

    if (!movingPiece->isValidMove(srcIndex, destIndex))
    {
        return 6;
    }
    currentPlayer.switchTurn();
    return 0; 
}
