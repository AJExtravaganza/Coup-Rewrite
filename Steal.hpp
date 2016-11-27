#pragma once

#include "Action.hpp"
#include "Block.hpp"

class Steal: public Action
{
private:
    Player* target;
    static const ActionID actionID = STEAL;

protected:

public:
    Steal(Player* _caster, std::vector<Player>& availablePlayers);
    Steal(const Steal& other);
    Steal& operator=(const Steal& other);
    virtual ~Steal();

    ActionID getActionID();
    void acquireTarget(std::vector<Player>& availablePlayers, std::istream& uiIn, std::ostream& uiOut);
    void checkForChallenge(std::vector<Player>& availablePlayers);
    Player* offerChallenge(Player* prospectiveChallenger);
    void challenge(Player* challenger);
    void checkForBlock(std::vector<Player>& availablePlayers);
    void block();
    void resolve();

};

