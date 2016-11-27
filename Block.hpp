#pragma once

#include "Action.hpp"

#include <vector>

class Block: public Action
{
private:
    Action* targetAction;
protected:

public:
    Block(Player* _caster, std::vector<Player>& availablePlayers, Action* _targetAction);
    Block(const Block& other);
    Block& operator=(const Block& other);
    virtual ~Block();

    void checkForChallenge(std::vector<Player>& availablePlayers);
    Player* offerChallenge(Player* prospectiveChallenger);
    void challenge(Player* challenger);
    void resolve();

};
