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

// TODO (Backbox#1#): killMe
/*Card::Card(const Card& other): role(other.role), name(other.name), exposed(other.exposed)
{

}

Card& Card::operator=(const Card& other)
{
    role = other.role;
    name = other.name;
    exposed = other.exposed;

    return *this;
}*/

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

