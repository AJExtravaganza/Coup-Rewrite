#include "Card.hpp"

Card::Card(): role(NullRole), name(""), exposed(true) {} //default constructor

Card::Card(Role _role): role(_role), name(""), exposed(false)
{
    switch (role)
    {
        case DUKE:
            name = "the Duke";
            break;
        case ASSASSIN:
            name = "the Assassin";
            break;
        case AMBASSADOR:
            name = "the Ambassador";
            break;
        case CAPTAIN:
            name = "the Captain";
            break;
        case CONTESSA:
            name = "the Contessa";
            break;
        case NullRole:
            name = "the NullCard";
        default:
            //throw exception
            break;
    }

}

bool Card::is(Role queriedRole)
{
    return (role == queriedRole);
}

std::string Card::getName()
{
    return name;
}

bool Card::isExposed()
{
    return exposed ? true : false;
}

void Card::expose()
{
    exposed = true;
}

