#include "Protocol.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "CheckCheck.h"
#include "SimpleCheck.h"


bool Protocol::isWhiteTurn = false;

Protocol::Protocol()
{
    this->_pieces.reserve(64);
    this->_pieces.push_back(new Rook("Black"));
    this->_pieces.push_back(new Knight("Black"));
    this->_pieces.push_back(new Bishop("Black"));
    this->_pieces.push_back(new Queen("Black"));
    this->_pieces.push_back(new King("Black"));
    this->_pieces.push_back(new Bishop("Black"));
    this->_pieces.push_back(new Knight("Black"));
    this->_pieces.push_back(new Rook("Black"));
    for (int i = 0; i < 8; ++i) {
        this->_pieces.push_back(new Pawn("Black"));
    }
    for (int i = 0; i < 32; ++i) {
        this->_pieces.push_back(nullptr);
    }
    for (int i = 0; i < 8; ++i) {
        this->_pieces.push_back(new Pawn("White"));
    }
    this->_pieces.push_back(new Rook("White"));
    this->_pieces.push_back(new Knight("White"));
    this->_pieces.push_back(new Bishop("White"));
    this->_pieces.push_back(new Queen("White"));
    this->_pieces.push_back(new King("White"));
    this->_pieces.push_back(new Bishop("White"));
    this->_pieces.push_back(new Knight("White"));
    this->_pieces.push_back(new Rook("White"));
}

Protocol::~Protocol()
{
    for (Piece* piece : _pieces) {
        delete piece;
    }
}

int Protocol::returnProtocolNum(const std::string& move)
{
    SimpleCheck checkSimple;
    CheckCheck checkCheck;
    std::string currentPlayer = isWhiteTurn ? "White" : "Black";
    int protocolNum = 0; 
    checkSimple.combineCheck(move, _pieces, currentPlayer);
    if (protocolNum == 0) 
    {
        protocolNum = checkCheck.checkGameState(_pieces, currentPlayer);
        if (protocolNum == 0 || protocolNum == 2 || protocolNum == 8) 
        {
            isWhiteTurn = !isWhiteTurn;
            this->swapSquares(move);
        }
    }

    return protocolNum;
}

void Protocol::swapSquares(const std::string& move)
{
    if (move.size() != 4) return;

    int current = (move[0] - 'a') + (8 * (7 - (move[1] - '1')));
    int dest = (move[2] - 'a') + (8 * (7 - (move[3] - '1')));
    this->_pieces[dest] = _pieces[current];
    this->_pieces[current] = nullptr;
}
