#include "Steal.hpp"

Steal::Steal(Player* _caster, std::vector<Player>& availablePlayers): Action(_caster), target(nullptr)
{
    isBluff = !(caster->hasInfluence(CAPTAIN));
    if (status == VALID)
    {
        acquireTarget(availablePlayers, *caster->uiIn, *caster->uiOut);

        *globalComms << caster->getName() << " claims the Captain, targeting " << target->getName() << ".\n";

        checkForChallenge(availablePlayers);
    }

    if (status == VALID)
    {
        checkForBlock(availablePlayers);
    }

    resolve();
}

Steal::Steal(const Steal& other): Action(other), target(other.target) //N.B This is how to correctly call a base-class constructor in a derived-class constructor.
{

}


Steal& Steal::operator=(const Steal& other)
{
    Action::operator=(other); //N.B This is how to correctly call the base-class assignment operator in a derived-class assignment operator.
    target = other.target;

    return *this;
}

Steal::~Steal()
{

}

ActionID Steal::getActionID()
{
    return actionID;
}

void Steal::acquireTarget(std::vector<Player>& availablePlayers, std::istream& uiIn, std::ostream& uiOut)
{
    int selection = -1;

    for (unsigned int player = 1; player <= availablePlayers.size(); player++)
    {
        if (&availablePlayers[player - 1] != caster)
        {
            uiOut << "[" << player << "] " << (availablePlayers[player - 1]).getName() << "\n";
        }
    }

    uiOut << "\nTargeting which player? ";

    selection = getSelection(1, availablePlayers.size(), uiIn, uiOut);
    target = &availablePlayers[selection - 1];

    while (target == caster)
    {
        uiOut << "You cannot target yourself.\n";
        selection = getSelection(1, availablePlayers.size(), uiIn, uiOut);
        target = &availablePlayers[selection - 1];
    }


}



void Steal::checkForChallenge(std::vector<Player>& availablePlayers)
{
    Player * challenger = nullptr;

// TODO (Backbox#1#): Change all instances of "player" in checkForChallenge() to "targetPlayer" for clarity
    for (unsigned int player = 0; player < availablePlayers.size()  && !challenger; player++)
    {
        if (&availablePlayers[player] != caster)
        {
            challenger = offerChallenge(&availablePlayers[player]);
        }
    }

    if (challenger)
    {
        *globalComms << challenger->getName() << " challenges " << caster->getName() << "'s claim to the Captain!\n";
        challenge(challenger);
    }
}

Player* Steal::offerChallenge(Player* prospectiveChallenger)
{
    *prospectiveChallenger->uiOut << prospectiveChallenger->getName() << ", would you like to challenge " << caster->getName() << "'s claim to the Captain? ";

    return (getSelection(*prospectiveChallenger->uiIn, *prospectiveChallenger->uiOut) ? prospectiveChallenger : nullptr);
}

void Steal::challenge(Player* challenger)
{
    if (isBluff)
    {
        *globalComms << caster->getName() << " was bluffing!\n";
        caster->sacrifice();
        status = CHALLENGED;
    }
    else
    {
        *globalComms << caster->getName() << " was not bluffing!\n";
        challenger->sacrifice();
    }
}

void Steal::checkForBlock(std::vector<Player>& availablePlayers)
{
    bool blocking = false;
    *target->uiOut << target->getName() << ", would you like to block? ";
    blocking = getSelection(*target->uiIn, *target->uiOut);

    if (blocking)
    {
        Block block = Block(target, availablePlayers, this);
    }

}

void Steal::block()
{
    status = BLOCKED;
}

void Steal::resolve()
{
    if (status == VALID)
    {
        *globalComms << caster->getName() << " steals two ISK from " << target->getName() << ".\n";
        target->takeIsk(2);
        caster->giveIsk(2);
    }

    status = RESOLVED;
}
