#pragma once

#include "Action.hpp"
#include "Block.hpp"

class Exchange: public Action
{
private:
    static const ActionID actionID = EXCHANGE;

protected:

public:
    Exchange(Player* _caster, std::vector<Player>& availablePlayers);
    Exchange(const Exchange& other);
    Exchange& operator=(const Exchange& other);
    virtual ~Exchange();

    ActionID getActionID();
    void checkForChallenge(std::vector<Player>& availablePlayers);
    Player* offerChallenge(Player* prospectiveChallenger);
    void challenge(Player* challenger);
    void resolve();

};

