#pragma once

#include "Action.hpp"
#include "Block.hpp"

class ~actionName: public Action
{
private:
    Player* target;
    static const ActionID actionID = ~actionLABEL;

protected:

public:
    ~actionName(Player* _caster, std::vector<Player>& availablePlayers);
    ~actionName(const ~actionName& other);
    ~actionName& operator=(const ~actionName& other);
    virtual ~~actionName();

    ActionID getActionID();
    void acquireTarget(std::vector<Player>& availablePlayers, std::istream& uiIn, std::ostream& uiOut);
    void checkForChallenge(std::vector<Player>& availablePlayers);
    Player* offerChallenge(Player* prospectiveChallenger);
    void challenge(Player* challenger);
    void checkForBlock(std::vector<Player>& availablePlayers);
    void block();
    void resolve();

};

