#pragma once

#include "Action.hpp"
#include "Block.hpp"

class Tax: public Action
{
private:
    static const ActionID actionID = TAX;

protected:

public:
    Tax(Player* _caster, std::vector<Player>& availablePlayers);
    Tax(const Tax& other);
    Tax& operator=(const Tax& other);
    virtual ~Tax();

    ActionID getActionID();
    void checkForChallenge(std::vector<Player>& availablePlayers);
    Player* offerChallenge(Player* prospectiveChallenger);
    void challenge(Player* challenger);
    void resolve();

};

