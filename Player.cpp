#include "Player.hpp"
#include "validation.hpp"

#include <string>


Player::Player(): playerID(-1), name("namelessplayer"), isk(0), stillAlive(false), hand({}), gameDeck(nullptr), uiIn(&std::cin), uiOut(&std::cout), globalComms(&std::cout){}

Player::Player(int _playerID, CoupDeck* _gameDeck): playerID(_playerID), name("namelessplayer"), isk(0), stillAlive(true), hand({}), gameDeck(_gameDeck), uiIn(&std::cin), uiOut(&std::cout), globalComms(&std::cout)
{
    *uiOut << "Player " << playerID << ", what is your name? ";
    std::string rawName;
    getline(*uiIn, rawName);
    name = (rawName.length() < 15 ? rawName : rawName.substr(0,15));
}


Player::Player(const Player& other): playerID(other.playerID), name(other.name), isk(other.isk), stillAlive(other.stillAlive), hand({}), gameDeck(other.gameDeck), uiIn(&std::cin), uiOut(&std::cout), globalComms(&std::cout)
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
// TODO (Backbox#1#): Can't I just assign other.hand to this.hand?
    for (unsigned int card = 0; card < other.hand.size(); card++)
    {
        hand.push_back(other.hand[card]);
    }
    gameDeck = other.gameDeck;
    uiIn = other.uiIn;
    uiOut = other.uiOut;
    globalComms = other.globalComms;


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

int Player::iskBalance()
{
    return isk;
}

bool Player::hasIsk(int cost) const
{
    return (isk >= cost);
}

void Player::giveNewCard(Card newCard)
{
    hand.push_back(newCard);
}

bool Player::hasInfluence(Role claimedRole)
{
    bool cardFound = false;

    for (unsigned int card = 0; card < hand.size(); card++)
    {
        if (hand[card].is(claimedRole) && !hand[card].isExposed())
        {
            cardFound = true;
        }
    }

    return cardFound;
}

// TODO (Backbox#1#): Dirty ad-hoc.  Pretty it up later.
std::string Player::listHand()
{
    std::string handString = "   ";

    for (unsigned int card = 0; card < hand.size(); card++)
    {
        if (hand[card].isExposed())
        {
            handString += "x-";
        }
        else
        {
            handString += "  ";
        }

        handString += (hand[card].getName().substr(4,3));
        handString += "   ";
    }

    for (unsigned int i = 0; i < handString.size(); i++)
    {
        handString[i] = toupper(handString[i]);
    }

    return handString;
}

void Player::playerDiscards(int requiredDiscards)
{
    *uiOut << "\n" << getName() << ", you currently have the following unexposed cards in your hand:\n";

    for (unsigned int card = 0; card < hand.size(); card++)
    {
        if (!hand[card].isExposed())
        {
            *uiOut << "[" << (card + 1) << "] " << hand[card].getName() << "\n"; // adds offset so cards are 1 to hand.size()
        }
    }

    *uiOut << "\n\nChoose " << requiredDiscards << " more " << (requiredDiscards == 1 ? "card" : "cards") << " to discard: ";

    unsigned int cardSelection = 0;
    do
    {
        cardSelection = (getSelection(1, hand.size(), *uiIn, *uiOut) - 1); //removes offset so elements are 0 to (hand.size() - 1)
    }while(hand[cardSelection].isExposed());

    gameDeck->putOnTop(hand[cardSelection]);
    hand.erase(begin(hand) + cardSelection);

    if (requiredDiscards > 1)
    {
        playerDiscards(requiredDiscards - 1);
    }

}

void Player::sacrifice()
{
    *uiOut << "\n" << getName() << ", you currently have the following unexposed cards in your hand:\n";

    for (unsigned int card = 0; card < hand.size(); card++)
    {
        if (!hand[card].isExposed())
        {
            *uiOut << "[" << (card + 1) << "] " << hand[card].getName() << "\n"; // adds offset so cards are 1 to hand.size()
        }
    }

    *uiOut << "\n\nChoose a card to sacrifice: ";

    int cardSelection = (getSelection(1, hand.size(), *uiIn, *uiOut) - 1); //removes offset so elements are 0 to (hand.size() - 1)
    hand[cardSelection].expose();

    *globalComms << "\n\n" << getName() << " exposes " << hand[cardSelection].getName() << "!\n";
}

void Player::killPlayer()
{
    stillAlive = false;
}

bool Player::isAlive()
{
    return stillAlive;
}
