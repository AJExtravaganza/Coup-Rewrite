#pragma once

#include "Card.hpp"
#include "enums.h"

#include <iostream>
#include <vector>

class Player
{
private:
    int playerID;
    std::string name;

    int isk;
// TODO (Backbox#1#): Upon project completion, check if still necessary
    bool stillAlive;
    std::vector<Card> hand;

public:
    Player();
    Player(int playerNumber);
    Player(const Player& other);
    Player& operator=(const Player& other);
    ~Player();

    std::istream* uiIn;
    std::ostream* uiOut;

    int getID() const;
    std::string getName() const;
    int currentIsk();
    void giveIsk(int quantity);
    void takeIsk(int quantity);
    bool hasIsk(int cost) const;
    void giveNewCard(Role card);
    bool hasCard(Role claimedRole);
    std::string listHand();
    bool willChallenge();
    void sacrifice();
    void exchange();
    void killPlayer();
    bool isAlive();

};
