#include "Action.hpp"

Action::Action(): status(NullStatus), caster(nullptr), isBluff(false), globalComms(&std::cout)
{

}

Action::Action(Player* _caster): status(VALID), caster (_caster), isBluff(false), globalComms(&std::cout)
{

}

Action::Action(const Action& other): status(other.status), caster(other.caster), isBluff(other.isBluff), globalComms(other.globalComms)
{

}


Action& Action::operator=(const Action& other)
{
    status = other.status;
    caster = other.caster;
    isBluff = other.isBluff;

    return *this;
}

Action::~Action()
{

}

std::string Action::getCasterName()
{
    return caster->getName();
}

ActionID Action::getActionID()
{
    return actionID;
}

void Action::block()
{
    std::cout << "ERROR: Call to undefined block()\n\n";
    //throw exception; only defined for blockable classes
}
