#pragma once

#include "Action.hpp"

class Income: public Action
{
private:
    static const ActionID actionID = INCOME;

protected:

public:
    Income(Player* _caster, std::vector<Player>& availablePlayers);
    Income(const Income& other);
    Income& operator=(const Income& other);
    virtual ~Income();

    ActionID getActionID();
    void resolve();

};

