
#include "`class.hpp"

`class::`class(Player* _caster, std::vector<Player>& availablePlayers): Action(_caster), target(nullptr)
{
    status = (caster->hasIsk(3) ? VALID : INSUFFICIENTFUNDS);
    isBluff = !(caster->hasInfluence(`ROLE));
    if (status == VALID)
    {
        acquireTarget(availablePlayers, *caster->uiIn, *caster->uiOut);

        *globalComms << caster->getName() << " claims the `Role, targeting " << target->getName() << ".\n";

        checkForChallenge(availablePlayers);
    }

    if (status == VALID)
    {
        checkForBlock(availablePlayers);
    }

    resolve();
}

`class::`class(const `class& other): Action(other), target(other.target) //N.B This is how to correctly call a base-class constructor in a derived-class constructor.
{

}


`class& `class::operator=(const `class& other)
{
    Action::operator=(other); //N.B This is how to correctly call the base-class assignment operator in a derived-class assignment operator.
    target = other.target;

    return *this;
}

`class::~`class()
{

}

ActionID `class::getActionID()
{
    return actionID;
}

void `class::acquireTarget(std::vector<Player>& availablePlayers, std::istream& uiIn, std::ostream& uiOut)
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



void `class::checkForChallenge(std::vector<Player>& availablePlayers)
{
    Player * challenger = nullptr;

    for (unsigned int player = 0; player < availablePlayers.size()  && !challenger; player++)
    {
        if (&availablePlayers[player] != caster)
        {
            challenger = offerChallenge(&availablePlayers[player]);
        }
    }

    if (challenger)
    {
        *globalComms << challenger->getName() << " challenges " << caster->getName() << "'s claim to the `Role!\n";
        challenge(challenger);
    }
}

Player* `class::offerChallenge(Player* prospectiveChallenger)
{
    *prospectiveChallenger->uiOut << prospectiveChallenger->getName() << ", would you like to challenge " << caster->getName() << "'s claim to the `Role? ";

    return (getSelection(*prospectiveChallenger->uiIn, *prospectiveChallenger->uiOut) ? prospectiveChallenger : nullptr);
}

void `class::challenge(Player* challenger)
{
    if (isBluff)
    {
        *globalComms << caster->getName() << " was bluffing!\n";
        caster->sacrifice();
    }
    else
    {
        *globalComms << caster->getName() << " was not bluffing!\n";
        challenger->sacrifice();
    }
}

void `class::checkForBlock(std::vector<Player>& availablePlayers)
{
    bool blocking = false;
    *target->uiOut << target->getName() << ", would you like to block? ";
    blocking = getSelection(*target->uiIn, *target->uiOut);

    if (blocking)
    {
        Block block = Block(target, availablePlayers, this);
    }

}

void `class::block()
{
    status = BLOCKED;
}

void `class::resolve()
{
    if (status == VALID)
    {
        *globalComms << caster->getName() << " `verbs " << target->getName() << ".\n";
        target->sacrifice();
    }

    status = RESOLVED;
}
