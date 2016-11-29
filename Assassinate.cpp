#include "Assassinate.hpp"

Assassinate::Assassinate(Player* _caster, std::vector<Player>& availablePlayers): Action(_caster), target(nullptr)
{
    status = (caster->hasIsk(3) ? VALID : INSUFFICIENTFUNDS);
    isBluff = !(caster->hasInfluenceOver(ASSASSIN));
    if (status == VALID)
    {
        acquireTarget(availablePlayers, *caster->uiIn, *caster->uiOut);

        *globalComms << caster->getName() << " claims the Assassin, targeting " << target->getName() << ".\n";

        checkForChallenge(availablePlayers);
    }

    if (status == VALID && caster->hasUnexposedCards() && target->hasUnexposedCards())
    {
        checkForBlock(availablePlayers);
    }

    if (target->hasUnexposedCards())
    {
        resolve();
    }
}

Assassinate::Assassinate(const Assassinate& other): Action(other), target(other.target) //N.B This is how to correctly call a base-class constructor in a derived-class constructor.
{

}


Assassinate& Assassinate::operator=(const Assassinate& other)
{
    Action::operator=(other); //N.B This is how to correctly call the base-class assignment operator in a derived-class assignment operator.
    target = other.target;

    return *this;
}

Assassinate::~Assassinate()
{

}

ActionID Assassinate::getActionID()
{
    return actionID;
}

void Assassinate::acquireTarget(std::vector<Player>& availablePlayers, std::istream& uiIn, std::ostream& uiOut)
{
    int selection = -1;

    for (int player = 1; player <= availablePlayers.size(); player++)
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



void Assassinate::checkForChallenge(std::vector<Player>& availablePlayers)
{
    Player * challenger = nullptr;

    for (int targetPlayer = 0; targetPlayer < availablePlayers.size()  && !challenger; targetPlayer++)
    {
        if (&availablePlayers[targetPlayer] != caster)
        {
            challenger = offerChallenge(&availablePlayers[targetPlayer]);
        }
    }

    if (challenger)
    {
        *globalComms << challenger->getName() << " challenges " << caster->getName() << "'s claim to the Assassin!\n";
        challenge(challenger);
    }
}

Player* Assassinate::offerChallenge(Player* prospectiveChallenger)
{
    *prospectiveChallenger->uiOut << prospectiveChallenger->getName() << ", would you like to challenge " << caster->getName() << "'s claim to the Assassin? ";

    return (getSelection(*prospectiveChallenger->uiIn, *prospectiveChallenger->uiOut) ? prospectiveChallenger : nullptr);
}

void Assassinate::challenge(Player* challenger)
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

void Assassinate::checkForBlock(std::vector<Player>& availablePlayers)
{
    bool blocking = false;
    *target->uiOut << target->getName() << ", would you like to block? ";
    blocking = getSelection(*target->uiIn, *target->uiOut);

    if (blocking)
    {
        Block block = Block(target, availablePlayers, this);
    }

}

void Assassinate::block()
{
    status = BLOCKED;
}

void Assassinate::resolve()
{
    if (status == VALID)
    {
        *globalComms << caster->getName() << " assassinates " << target->getName() << ".\n";
        caster->takeIsk(3);
        target->sacrifice();
    }
    else if (status == BLOCKED)
    {
        caster->takeIsk(3);
    }

    status = RESOLVED;
}
