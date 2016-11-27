#pragma once

#include "Action.hpp"
#include "Block.hpp"

class ForeignAid: public Action
{
private:
    static const ActionID actionID = FOREIGN_AID;

protected:

public:
    ForeignAid(Player* _caster, std::vector<Player>& availablePlayers);
    ForeignAid(const ForeignAid& other);
    ForeignAid& operator=(const ForeignAid& other);
    virtual ~ForeignAid();

    ActionID getActionID();
    void checkForBlock(std::vector<Player>& availablePlayers);
    Player* offerBlock(Player* prospectiveBlocker);
    void block();
    void resolve();

};

