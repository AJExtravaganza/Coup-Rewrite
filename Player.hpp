#pragma once

#include "Card.hpp"
#include "CoupDeck.hpp"
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
    bool isAlive;
    std::vector<Card> hand;

public:
    Player();
    Player(int playerNumber, CoupDeck* _gameDeck);
    Player(const Player& other);
    Player& operator=(const Player& other);
    ~Player();

    CoupDeck* gameDeck;
    std::istream* uiIn;
    std::ostream* uiOut;
    std::ostream* globalComms;

    int getID() const;
    std::string getName() const;
    int currentIsk();
    void giveIsk(int quantity);
    void takeIsk(int quantity);
    int iskBalance();
    bool hasIsk(int cost) const;
    void giveNewCard(Card newCard);
    bool hasInfluenceOver(Role claimedRole);
    std::string listHand();
    std::string listHandInline();
    void listHandInline(std::ostream& out);
    void playerDiscards(int requiredDiscards);
    bool willChallenge();
    void sacrifice();
    void exchange();
    bool hasUnexposedCards();
    void killPlayer();

};
