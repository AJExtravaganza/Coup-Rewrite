#include "Card.hpp"
#include "enums.h"
#include "Player.hpp"

#include <string>


Player::Player(): playerID(-1), name("namelessplayer"), isk(0), stillAlive(false), hand({}), uiIn(&std::cin), uiOut(&std::cout){}

Player::Player(int _playerID): playerID(_playerID), name("namelessplayer"), isk(0), stillAlive(true), hand({}), uiIn(&std::cin), uiOut(&std::cout)
{
    *uiOut << "Player " << playerID << ", what is your name? ";
    std::string rawName;
    getline(*uiIn, rawName);
    name = (rawName.length() < 15 ? rawName : rawName.substr(0,15));
}


Player::Player(const Player& other): playerID(other.playerID), name(other.name), isk(other.isk), stillAlive(other.stillAlive), hand({}), uiIn(&std::cin), uiOut(&std::cout)
{
    for (unsigned int card = 0; card < other.hand.size(); card++)
    {
        hand.push_back(other.hand[card]);
    }
}

Player& Player::operator=(const Player& other)
{
    playerID = other.playerID;
    name = other.name;
    isk = other.isk;
    stillAlive = other.stillAlive;
    hand = {};
    for (unsigned int card = 0; card < other.hand.size(); card++)
    {
        hand.push_back(other.hand[card]);
    }

    return *this;

}

Player::~Player()
{

}

int Player::getID() const
{
    return playerID;
}

std::string Player::getName() const
{
    return name;
}

int Player::currentIsk()
{
    return isk;
}

void Player::giveIsk(int quantity)
{
    isk += quantity;
}

void Player::takeIsk(int quantity)
{
    isk -= quantity;
}

bool Player::hasIsk(int cost) const
{
    return (isk >= cost);
}

void Player::giveNewCard(Role card)
{
    hand.push_back(Card(card));
}

bool Player::hasCard(Role claimedRole)
{
    bool cardFound = false;

    for (unsigned int card = 0; card < hand.size(); card++)
    {
        if (hand[card].is(claimedRole))
        {
            cardFound = true;
        }
    }

    return cardFound;
}

std::string Player::listHand()
{
    std::string handString = "";

    for (unsigned int card = 0; card < hand.size(); card++)
    {
        if (hand[0].isExposed())
        {
            handString += "exposed-";
        }

        handString += hand[card].getName();
        handString += " ";
    }

    return handString;
}

void Player::sacrifice()
{
    std::cout << getName() << " sacrifices a card." << std::endl;
}
void Player::exchange()
{
    std::cout << getName() << " exchanges card(s)" << std::endl;
}

void Player::killPlayer()
{
    stillAlive = false;
}

bool Player::isAlive()
{
    return stillAlive;
}
