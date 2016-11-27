#pragma once

#include "Action.hpp"

class Coup: public Action
{
private:
    Player* target;
    static const ActionID actionID = COUP;

protected:

public:
    Coup(Player* _caster, std::vector<Player>& availablePlayers);
    Coup(const Coup& other);
    Coup& operator=(const Coup& other);
    virtual ~Coup();

    ActionID getActionID();
    void acquireTarget(std::vector<Player>& availablePlayers, std::istream& uiIn, std::ostream& uiOut);
    void resolve();

};

