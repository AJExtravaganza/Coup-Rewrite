/*
// TODO (Backbox#1#): Constructors/destructors for all relevant classes.
// TODO (Backbox#1#): CURRENT STATUS: ...
//
//Challenging and blocking successfully implemented on assassinate.
//
//TO DO:
//
// - Player, hand and deck initialisation
// - Implementation of other actions

    AUTHOR: ALEXANDER DUNN
    PROJECT NAME:
    PROJECT DESCRIPTION:
    PROJECT STARTED:
*/

#include "Assassinate.hpp"

#include "stdlib.h"

int main()
{

    std::vector<Player> playersAtTable = {};

    playersAtTable.push_back(Player(1));
    playersAtTable[0].giveNewCard(ASSASSIN);
    playersAtTable[0].giveNewCard(DUKE);
    playersAtTable[0].giveIsk(3);

    playersAtTable.push_back(Player(2));
    playersAtTable[1].giveNewCard(ASSASSIN);
    playersAtTable[1].giveNewCard(DUKE);
    playersAtTable[1].giveIsk(3);


    Assassinate newAction= Assassinate(&playersAtTable[0], playersAtTable);

    system("pause");

    return 0;
}
