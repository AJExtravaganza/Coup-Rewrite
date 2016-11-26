#pragma once

#include "Player.hpp"
//#include "validation.hpp"

#include <iostream>

class Action
{
private:

protected:
    ActionStatus status;
    Player* caster;
    bool isBluff;
public:
    Action();
    Action(Player* _caster);
    Action(const Action& other);
    Action& operator=(const Action& other);
    virtual ~Action();

    static const ActionID actionID = NullAction;
    std::ostream* globalComms;

// TODO (Backbox#1#): Check later if this needs to be virtual or whether I can just define it here and have the calls still work.
    virtual ActionID getActionID();
    virtual void block();
    virtual void resolve() = 0;

};
