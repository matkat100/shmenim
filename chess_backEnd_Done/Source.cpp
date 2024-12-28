/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include "CheckCheck.h"
#include "Piece.h"
#include "King.h"
#include <iostream>
#include <thread>
#include <vector>
using std::cout;
using std::endl;
using std::string;


void main()
{
	srand(time_t(NULL));


	Pipe p;
	bool isConnect = p.connect();

	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return;
		}
	}


	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1"); // just example...

	p.sendMessageToGraphics(msgToGraphics);   // send the board string
	std::vector<Piece*> pieces(64, nullptr);
	CheckCheck checker;
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
        string source = msgFromGraphics.substr(0, 2);
        string destination = msgFromGraphics.substr(2, 2);

        int protocolResult = Protocol::returnProtocolNum(msgFromGraphics);

        if (protocolResult == 2)
        {
            strcpy_s(msgToGraphics, "2");
        }
        else if (protocolResult == 3)
        {
            strcpy_s(msgToGraphics, "3"); 
        }
        else if (protocolResult == 5)
        {
            strcpy_s(msgToGraphics, "5"); 
        }
        else if (protocolResult == 6)
        {
            strcpy_s(msgToGraphics, "6"); 
        }
        else if (protocolResult == 7)
        {
            strcpy_s(msgToGraphics, "7");
        }
        else if (protocolResult == 0)
        {
            strcpy_s(msgToGraphics, "0"); 
        }
        else
        {
            strcpy_s(msgToGraphics, "Invalid protocol result");
        }

        p.sendMessageToGraphics(msgToGraphics);
        msgFromGraphics = p.getMessageFromGraphics();
    }
    p.close();
}