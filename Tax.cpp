#include "Tax.hpp"

Tax::Tax(Player* _caster, std::vector<Player>& availablePlayers): Action(_caster)
{
    isBluff = !(caster->hasInfluenceOver(DUKE));
    if (status == VALID)
    {
        *globalComms << caster->getName() << " claims the Duke, and intends to collect tax.\n";

        checkForChallenge(availablePlayers);
    }

    if(caster->hasUnexposedCards())
    {
        resolve();
    }
}

Tax::Tax(const Tax& other): Action(other) //N.B This is how to correctly call a base-class constructor in a derived-class constructor.
{

}


Tax& Tax::operator=(const Tax& other)
{
    Action::operator=(other); //N.B This is how to correctly call the base-class assignment operator in a derived-class assignment operator.

    return *this;
}

Tax::~Tax()
{

}

ActionID Tax::getActionID()
{
    return actionID;
}

void Tax::checkForChallenge(std::vector<Player>& availablePlayers)
{
    Player * challenger = nullptr;

    for (int player = 0; player < availablePlayers.size()  && !challenger; player++)
    {
        if (&availablePlayers[player] != caster)
        {
            challenger = offerChallenge(&availablePlayers[player]);
        }
    }

    if (challenger)
    {
        *globalComms << challenger->getName() << " challenges " << caster->getName() << "'s claim to the Duke!\n";
        challenge(challenger);
    }
}

Player* Tax::offerChallenge(Player* prospectiveChallenger)
{
    *prospectiveChallenger->uiOut << prospectiveChallenger->getName() << ", would you like to challenge " << caster->getName() << "'s claim to the Duke? ";

    return (getSelection(*prospectiveChallenger->uiIn, *prospectiveChallenger->uiOut) ? prospectiveChallenger : nullptr);
}

void Tax::challenge(Player* challenger)
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

void Tax::resolve()
{
    if (status == VALID)
    {
        *globalComms << caster->getName() << " collects tax of three ISK.\n";
        caster->giveIsk(3);
    }

    status = RESOLVED;
}
