#include "ForeignAid.hpp"

ForeignAid::ForeignAid(Player* _caster, std::vector<Player>& availablePlayers): Action(_caster)
{

    *globalComms << caster->getName() << " intends to take foreign aid.\n";

    checkForBlock(availablePlayers);

    resolve();
}

ForeignAid::ForeignAid(const ForeignAid& other): Action(other) //N.B This is how to correctly call a base-class constructor in a derived-class constructor.
{

}


ForeignAid& ForeignAid::operator=(const ForeignAid& other)
{
    Action::operator=(other); //N.B This is how to correctly call the base-class assignment operator in a derived-class assignment operator.

    return *this;
}

ForeignAid::~ForeignAid()
{

}

ActionID ForeignAid::getActionID()
{
    return actionID;
}

void ForeignAid::checkForBlock(std::vector<Player>& availablePlayers)
{
    bool blocking = false;

    Player * blocker = nullptr;

    for (unsigned int player = 0; player < availablePlayers.size()  && !blocker; player++)
    {
        if (&availablePlayers[player] != caster)
        {
            blocker = offerBlock(&availablePlayers[player]);
        }
    }

    if (blocker)
    {
        *globalComms << blocker->getName() << " claims the Duke, and attempts to block " << caster->getName() << "'s foreign aid!\n";
        Block block = Block(blocker, availablePlayers, this);
    }
}

Player* ForeignAid::offerBlock(Player* prospectiveBlocker)
{
    *prospectiveBlocker->uiOut << prospectiveBlocker->getName() << ", would you like to block " << caster->getName() << "'s foreign aid? ";

    return (getSelection(*prospectiveBlocker->uiIn, *prospectiveBlocker->uiOut) ? prospectiveBlocker : nullptr);
}

void ForeignAid::block()
{
    status = BLOCKED;
}

void ForeignAid::resolve()
{
    if (status == VALID)
    {
        *globalComms << caster->getName() << " collects foreign aid of two ISK.\n";
        caster->giveIsk(2);
    }

    status = RESOLVED;
}
