/*
// TODO (Backbox#1#): Constructors/destructors for all relevant classes.
// TODO (Backbox#1#): CURRENT STATUS: ...
//
// Initialisation and all actions implemented/tested.
// Challenges tested
// All blocking tested
// Card exposure tested wrt bluffing and exchange.
//
//TO DO:
//
//
// - Implement some kind of ui
// - Implement player death
// - Implement win detection

    AUTHOR: ALEXANDER DUNN
    PROJECT NAME:
    PROJECT DESCRIPTION:
    PROJECT STARTED:
*/
// TODO (Backbox#1#): Implement player death
// TODO (Backbox#1#): Implement win detection

#include "CoupActions.hpp"
#include "CoupDeck.hpp"

#include <iomanip>
#include <time.h>
#include "stdlib.h"

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
    int activePlayersAtTurnStart = desiredPlayers;
    serverInput->ignore();

    for (int i = 0; i < desiredPlayers; i++)
    {
        activePlayers.push_back(Player(i, &gameDeck));
        activePlayers[i].giveIsk(10);
        activePlayers[i].giveNewCard(gameDeck.draw());
        activePlayers[i].giveNewCard(gameDeck.draw());
    }

    for (int i = 0; activePlayers.size() > 1; i = ((i + 1 + activePlayers.size()) % activePlayersAtTurnStart))
    {
        activePlayersAtTurnStart = activePlayers.size();
        processTurn(activePlayers, (&activePlayers[0] + i), globalComms);

    }


    return 0;
}

void processTurn(std::vector<Player>& activePlayers, Player* activePlayer, std::ostream* globalComms)
{
    int menuSelection = -1;
    Action* activeAction = nullptr;

    *globalComms << "\n\n\n" << activePlayer->getName() << " is the active player\n\n";

    boardState(activePlayers, globalComms);

    *activePlayer->uiOut << *activePlayer.getName() << ", you have the following card(s) in your hand: \n" << activePlayer->listHand() << ".\n"
                       << "You have " << activePlayer->iskBalance() << " ISK.\n\n"
                       << "Which action would you like to take? [1-7]\n\n"
                       << "[1] Take income\n"
                       << "[2] Take foreign aid\n"
                       << "[3] Stage a coup\n"
                       << "[4] Tax\n"
                       << "[5] Assassinate\n"
                       << "[6] Exchange\n"
                       << "[7] Steal\n\n"
                       << "Your choice: ";

    menuSelection = getSelection(1, 7, *activePlayer->uiIn, *activePlayer->uiOut);

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
    for (unsigned int i = 0; i < activePlayers.size(); i++)
    {
        *globalComms << std::left
                     << std::setw(15) << activePlayers[i].getName()
                     << std::setw(2) << activePlayers[i].iskBalance() << "ISK"
                     << activePlayers[i].listHand() << "\n";
    }

    *globalComms << std::endl;
}

