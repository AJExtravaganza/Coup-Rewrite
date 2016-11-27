#include "Coup.hpp"

Coup::Coup(Player* _caster, std::vector<Player>& availablePlayers): Action(_caster), target(nullptr)
{
    status = (caster->hasIsk(7) ? VALID : INSUFFICIENTFUNDS);
    if (status == VALID)
    {
        acquireTarget(availablePlayers, *caster->uiIn, *caster->uiOut);

        *globalComms << caster->getName() << " stages a coup, targeting " << target->getName() << "!\n";
    }

    resolve();
}

Coup::Coup(const Coup& other): Action(other), target(other.target) //N.B This is how to correctly call a base-class constructor in a derived-class constructor.
{

}


Coup& Coup::operator=(const Coup& other)
{
    Action::operator=(other); //N.B This is how to correctly call the base-class assignment operator in a derived-class assignment operator.
    target = other.target;

    return *this;
}

Coup::~Coup()
{

}

ActionID Coup::getActionID()
{
    return actionID;
}

void Coup::acquireTarget(std::vector<Player>& availablePlayers, std::istream& uiIn, std::ostream& uiOut)
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

void Coup::resolve()
{
    if (status == VALID)
    {
        *globalComms << caster->getName() << " overthrows " << target->getName() << ".\n";
        caster->takeIsk(7);
        target->sacrifice();
    }

    status = RESOLVED;
}

