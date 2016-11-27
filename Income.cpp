#include "Income.hpp"

Income::Income(Player* _caster, std::vector<Player>& availablePlayers): Action(_caster)
{

    *globalComms << caster->getName() << " intends to take income.\n";

    resolve();
}

Income::Income(const Income& other): Action(other) //N.B This is how to correctly call a base-class constructor in a derived-class constructor.
{

}


Income& Income::operator=(const Income& other)
{
    Action::operator=(other); //N.B This is how to correctly call the base-class assignment operator in a derived-class assignment operator.

    return *this;
}

Income::~Income()
{

}

ActionID Income::getActionID()
{
    return actionID;
}

void Income::resolve()
{
    if (status == VALID)
    {
        *globalComms << caster->getName() << " collects income of one ISK.\n";
        caster->giveIsk(1);
    }

    status = RESOLVED;
}
