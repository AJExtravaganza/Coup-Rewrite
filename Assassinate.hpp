#pragma once
#include "Action.hpp"
#include "Player.hpp"

class Assassinate: public Action
{
private:
    Player* target;
    static const ActionID actionID = ASSASSINATE;

protected:

public:
    Assassinate(Player* _caster, std::vector<Player>& availablePlayers);
    Assassinate(const Assassinate& other);
    Assassinate& operator=(const Assassinate& other);
    virtual ~Assassinate();

    ActionID getActionID();
    void acquireTarget(std::vector<Player>& availablePlayers, std::istream& uiIn, std::ostream& uiOut);
    void checkForChallenge(std::vector<Player>& availablePlayers);
    Player* offerChallenge(Player* prospectiveChallenger);
    void challenge(Player* challenger);
    void checkForBlock(std::vector<Player> availablePlayers);
    void block();
    void resolve();

};
