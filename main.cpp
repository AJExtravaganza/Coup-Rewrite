/*
// TODO (Backbox#1#): CURRENT STATUS: ...
//
// Game complete and tested.
//
//TO DO:
// - Implement some kind of ui
// - Implement some kind of multiplayer

    AUTHOR: ALEXANDER DUNN
    PROJECT NAME:
    PROJECT DESCRIPTION:
    PROJECT STARTED:
*/

#include "CoupActions.hpp"
#include "CoupDeck.hpp"

#include <iomanip>
#include <time.h>
#include "stdlib.h"

void initialise(int numberOfPlayers, std::vector<Player>& players, CoupDeck gameDeck);
void processTurn(std::vector<Player>& activePlayers, Player* activePlayer, std::ostream* globalComms);
void boardState(std::vector<Player>& activePlayers, std::ostream* globalComms);

int main()
{
    srand(time(nullptr));
    std::istream* serverInput = &std::cin;
    std::ostream* globalComms = &std::cout;

    CoupDeck gameDeck;
    std::vector<Player> activePlayers;
    *globalComms << "How many players? ";
    int desiredPlayers = getSelection(2, 6, *serverInput, *globalComms);
    serverInput->ignore();

    initialise(desiredPlayers, activePlayers, gameDeck);

    for (int i = 0; activePlayers.size() > 1; i = ((i + 1) % activePlayers.size()))
    {
        system("cls");

        processTurn(activePlayers, (&activePlayers[0] + i), globalComms);
        for (int j = 0; j < activePlayers.size(); j++)
        {
            if (!activePlayers[j].hasUnexposedCards())
            {
                activePlayers.erase(begin(activePlayers) + j);

                if (j <= i)
                {
                    i--;
                }

                j--;
            }
        }

        system("pause");
    }

    *globalComms << activePlayers[0].getName() << " wins the game, holding " << activePlayers[0].listHandInline() << "!\n\n";


    return 0;
}

void initialise(int desiredPlayers, std::vector<Player>& players, CoupDeck gameDeck)
{
    for (int i = 0; i < desiredPlayers; i++)
    {
        players.push_back(Player(i, &gameDeck));
        players[i].giveIsk(3);
        players[i].giveNewCard(gameDeck.draw());
        players[i].giveNewCard(gameDeck.draw());
    }
}

void processTurn(std::vector<Player>& activePlayers, Player* activePlayer, std::ostream* globalComms)
{
    int menuSelection = -1;
    Action* activeAction = nullptr;

    *globalComms << activePlayer->getName() << " is the active player\n\n";

    boardState(activePlayers, globalComms);

    *activePlayer->uiOut << activePlayer->getName() << ", you have the following card(s) in your hand: \n" << activePlayer->listHandInline() << ".\n"
                         << "You have " << activePlayer->iskBalance() << " ISK.\n\n";

    if (activePlayer->hasIsk(10))
    {
        *globalComms << activePlayer->getName() << " has ten or more ISK, and must perform a Coup!\n\n";
        menuSelection = 3;
    }
    else
    {
        *activePlayer->uiOut << "Which action would you like to take? [1-7]\n\n"
                             << "[1] Take income\n"
                             << "[2] Take foreign aid\n"
                             << "[3] Stage a coup\n"
                             << "[4] Tax\n"
                             << "[5] Assassinate\n"
                             << "[6] Exchange\n"
                             << "[7] Steal\n\n"
                             << "Your choice: ";

        menuSelection = getSelection(1, 7, *activePlayer->uiIn, *activePlayer->uiOut);
    }

    switch(menuSelection)
    {
    case 1:
        activeAction = new Income(activePlayer, activePlayers);
        break;
    case 2:
        activeAction = new ForeignAid(activePlayer, activePlayers);
        break;
    case 3:
        activeAction = new Coup(activePlayer, activePlayers);
        break;
    case 4:
        activeAction = new Tax(activePlayer, activePlayers);
        break;
    case 5:
        activeAction = new Assassinate(activePlayer, activePlayers);
        break;
    case 6:
        activeAction = new Exchange(activePlayer, activePlayers);
        break;
    case 7:
        activeAction = new Steal(activePlayer, activePlayers);
        break;
    default:
        *globalComms << "You broke something.  Good job dickhead.\n\n";
        //throw exception
        break;
    }

    delete activeAction;
}


void boardState(std::vector<Player>& activePlayers, std::ostream* globalComms)
{
    for (int i = 0; i < activePlayers.size(); i++)
    {
        *globalComms << std::left
                     << std::setw(15) << activePlayers[i].getName()
                     << std::setw(2) << activePlayers[i].iskBalance() << "ISK"
                     << activePlayers[i].listHandBrief() << "\n";
    }

    *globalComms << std::endl;
}

