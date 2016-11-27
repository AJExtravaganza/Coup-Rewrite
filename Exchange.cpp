#include "Exchange.hpp"

Exchange::Exchange(Player* _caster, std::vector<Player>& availablePlayers): Action(_caster)
{
    status = (caster->hasIsk(3) ? VALID : INSUFFICIENTFUNDS);
    isBluff = !(caster->hasInfluenceOver(AMBASSADOR));
    if (status == VALID)
    {
        *globalComms << caster->getName() << " claims the Ambassador, and intends to exchange cards.\n";

        checkForChallenge(availablePlayers);
    }
    if (caster->hasUnexposedCards())
    {
        resolve();
    }
}

Exchange::Exchange(const Exchange& other): Action(other) //N.B This is how to correctly call a base-class constructor in a derived-class constructor.
{

}


Exchange& Exchange::operator=(const Exchange& other)
{
    Action::operator=(other); //N.B This is how to correctly call the base-class assignment operator in a derived-class assignment operator.

    return *this;
}

Exchange::~Exchange()
{

}

ActionID Exchange::getActionID()
{
    return actionID;
}

void Exchange::checkForChallenge(std::vector<Player>& availablePlayers)
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
        *globalComms << challenger->getName() << " challenges " << caster->getName() << "'s claim to the Ambassador!\n";
        challenge(challenger);
    }
}

Player* Exchange::offerChallenge(Player* prospectiveChallenger)
{
    *prospectiveChallenger->uiOut << prospectiveChallenger->getName() << ", would you like to challenge " << caster->getName() << "'s claim to the Ambassador? ";

    return (getSelection(*prospectiveChallenger->uiIn, *prospectiveChallenger->uiOut) ? prospectiveChallenger : nullptr);
}

void Exchange::challenge(Player* challenger)
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

void Exchange::resolve()
{
    if (status == VALID)
    {
        caster->giveNewCard(caster->gameDeck->draw());
        caster->giveNewCard(caster->gameDeck->draw());
        caster->playerDiscards(2);
        caster->gameDeck->shuffle();


        *globalComms << caster->getName() << " exchanged cards.\n";
    }
    status = RESOLVED;
}
